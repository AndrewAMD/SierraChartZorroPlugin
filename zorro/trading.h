//////////////////////////////////////////////////////////////////////
// Zorro-specific variables & functions
// for use by lite-C scripts & Zorro program
// (c) oP group 2014, 2019
//////////////////////////////////////////////////////////////////////
#ifndef trading_h
#define trading_h

/////////////////////////////////////////////////////////////////////
// convenience definitions
typedef double var;
typedef var* vars;
typedef char* string;
typedef long function;

#define and &&
#define or ||
#define not !
#define as_int(x) *((int*)&(x))
#define PI	3.14159
#define NIL 3e38

/////////////////////////////////////////////////////////////////////
// constant limits (don't change!)
#define NAMESIZE		16		// asset and algo names
#define NAMESIZE2		40		// broker and account names
#define NUM_SKILLS	8
#define NUM_SKILLS2	16
#define NUM_RESULTS	20
#define MAX_PARAMS	16		// max optimize() calls per component
#define MAX_STEPS		1000	// max optimize() steps
#define MAX_CORES		72		// max cores for WFO training
#define MAX_ASSETS	8000	// max assets in list
#define MAX_CONTRACTS 20000 // max size of CONTRACTS chain
#define MAX_QUOTES	5000	// size of T2 orderbook list
#define MAX_BUFFER	20000	// size of text buffers

/////////////////////////////////////////////////////////////////////
// trading structs
typedef struct T1
{
	DATE	time;	// GMT timestamp, OLE datetime, 0.5 ms precision
	float fVal;	// positive for ask, negative for bid	
} T1; // single-stream tick, .t1 file content

typedef struct T2
{
  DATE  time; // GMT timestamp
  float fVal; // price quote, positive for ask and negative for bid
  float fVol; // volume / size
} T2; // order book data

typedef struct THL
{
	DATE	time;	
	float fHigh, fLow;	
} THL; // two-stream tick, internal format

typedef struct T6
{
	DATE	time;			// GMT timestamp of fClose
	float fHigh, fLow;	// (f1,f2)
	float fOpen, fClose;	// (f3,f4)	
	float fVal, fVol; // additional data, f.i. spread and volume (f5,f6)
} T6; // 6-stream tick, .t6 file content

typedef struct CONTRACT
{
	DATE	time;			// live: trading class string
	float fAsk, fBid; // premium without multiplier (f1,f2)
	float fVal;			// script dependent - bid volume, IV, delta... (f3)
	float fVol;			// trade volume, ask volume, or open interest (f4)
	float fUnl;			// unadjusted underlying price (f5)
	float fStrike;		// (f6)
	long	Expiry;		// YYYYMMDD (i7)
	long	Type;			// PUT, CALL, FUTURE, EUROPEAN, BINARY (s8)
} CONTRACT; // for options, futures, FOPs

typedef struct COMBO
{
	CONTRACT *Leg[4];
	int	N[4];
} COMBO;

typedef struct BAR
{
	DATE	time_base,time_span;		// start and duration of the bar in GMT time zone
} BAR;

typedef struct DATA
{
	int	start,end;	// first and last plotted data in the array
	var*	Data;			// data array
} DATA;

typedef struct PARAMETER	// parameter list
{
	var Value,Min,Max,Step,Best;
	char Name[40];
} PARAMETER;

typedef struct DATASET
{
	int	rows,cols;	// records and fields
	int	allocrows;	// allocated records, or 0
	float*	fData;	// data array
} DATASET;

typedef struct MATRIX
{
  int rows,cols,total;
  var* dat;
} MATRIX;

typedef MATRIX*  mat;
#define me(M,row,col)	*(M->dat+(row)*M->cols+(col)) 
#define ve(M,n)			*(M->dat+(n)) 

//////////////////////////////////////////////////////////////
// objects
typedef struct ASSET
{
	var	vPrice;	// last ask price
	var	vSpread; // difference between ask and bid prices
	var	vRollLong,vRollShort;	// interest for short and long position rollover per 10K
	var	vPIP;		// conversion factor Pip -> Price (0.0001 for most currencies, 1 for most CFDs)
	var	vPIPCost;		// cost of one Pip per lot, in account currency
	var	vMarginCost;	// broker's margin cost per lot (usually between 5 and 100), determining the leverage
	var	vLeverage;		// buying power
	var	vLotAmount;		// number of contracts per lot
	var	vFactor,vOffset;	// for normalizing price ticks
	var	vCommission;	// commission per 10K, in account currency
	var	vSlipPerSec;	// price difference per second by slippage
	var	vInitialPrice;	// from the asset parameters
	var	vStrength;		// currency strength difference
	var	vVal,vVol;		// volume data or quote frequencies
	var	tAsk,tBid;		// time stamp of last quote
	var	vEntryLimit,vExitLimit;	// for adaptive algos
	var	vWinPayout,vLossPayout;	// payouts in percent for binary trading
	var	*pOpen,*pClose,*pHigh,*pLow,*pPrice;	// price history data array
	var	*pVal,*pVol;	// additional price data lists, f.i. spread and volume
	CONTRACT *pContracts;	// contract chain
	void	**pTicks;		// tick pointer array, used for tick simulation in trade functions
	void	*tick_start,*tick_end;	// tick list in THL or T6 format, dependent on LEAN
	void	*tick_mem;		// allocated tick memory
	int	nTotalTicks;	// number of ticks in tick_mem
	int	nFirstPriceBar; // first simulation bar for this asset
	int	nLastPriceBar;	// last simulation bar for this asset
	int	nBar,nCounter,nOffset;
	int	nMaxLots;		// Max # of lots per trade
	int	flags;
	int	nSkipped,nFrame;	// distance to the last bar with a price quote
	int	nNetSum,nVirtualSum; // number of lots of all open pool and virtual trades
	int	nExtSum;			// number of lots of externally closed trades
	int	nPhantomSum;	// number of lots of open phantom trades
	int	nZone,nHour;	// asset time zone
	int	nMarket;			// timezone for not trading outside market hours
	int	nMultiplier;	// options multiplier
	int	numContracts;	// number of contracts
	int	nHandle;			// handle of options/futures dataset, + year <<16
	int	nContractRow,nContractOffs;	// dataset numbers of the found contract
	T6		Tick;				// current tick of the asset in the backtest
	char	sName[NAMESIZE];	// short name of the asset
	char	sSymbol[NAMESIZE2];	// broker symbol of the asset
	char	sSymbolLive[NAMESIZE2];	// symbol for live prices
	char	sSymbolHist[NAMESIZE2];	// symbol for historical prices
	char	sSourceTrade[NAMESIZE];	// asset price source, if not the broker
	char	sSourceLive[NAMESIZE];	// asset price source, if not the broker
	char	sSourceHist[NAMESIZE];	// asset price source, if not the broker
	var	Skill[NUM_SKILLS2]; // asset-specific general purpose variables
	int	nCentage;		// prices in cents
	string sExchange;		// Exchange for options 
	int	nTradeCounter;	// BrokerTrade update counter for g->nTradeRate
	void	*Cache;			// Pointer for data cache, NULL when dirty
	int	nCache;			// Number of memory pool
	var	vBarAvg,vValAvg,vVolAvg;	// Average price, vol, val of one bar, intermediate value
	var	vBack[8];		// price backup for intrabar simulation
} ASSET;

typedef struct TRADE
{
	float	fEntryPrice;	// buy price, or premium without multiplicator
	float	fExitPrice;	// sell price per unit, without spread
	float fResult;		// current profit of the trade
	float	fEntryLimit;	// buy entry limit
	float	fProfitLimit;	// profit limit price
	float fTrailLock;	// profit target distance to initial price, positive (long) or negative (short)
	float	fStopLimit;	// stop loss limit price
	float	fStopDiff;	// signed stop loss distance to initial price, positive (short) or negative (long)
	float	fTrailLimit;	// trail limit price
	float	fTrailDiff;	// signed stop loss adaption distance, positive (short) or negative (long)
	float	fTrailSlope;	// stop loss adaption factor, 0..1
	float	fTrailStep;	// stop loss bar step factor, 0..1
	float	fSpread;		// spread at entry for short, current spread for long trades
	float	fMAE,fMFE;	// Max adverse excursion, max favorite excursion without slippage, spread etc.
	float fRoll;		// accumulated rollover, < 0
	float fSlippage;	// Slippage, < 0
	float	fUnits;		// conversion factor asset price -> account currency per lot. fUnits = vPIPCost/vPIP or Multiplier.
	float	fTrailSpeed;	// break even speed factor 
	int	nExitTime;	// sell at market after this number of bars
	int	nEntryTime;	// wait this number of bars for entry limit orders
	int	nLots;		// filled Lots
	int	nBarOpen;	// bar number of order and entry
	int	nBarClose;	// current bar number while open, otherwise exit bar number
	int	nID;			// active trade id / order id; can change when trades are partially closed
	DATE	tEntryDate;	// entry time target
	DATE	tExitDate;	// exit time target
	DWORD flags;		// trade flags, see below
	float	fArg[8];		// TMF arguments
	var	Skill[NUM_SKILLS];	// general purpose variables for TMF
	int	nContract;	// contract type & exchange code
	float	fStrike;		// contract strike price
	float	fUnl;			// contract underlying price, needed for futures
	char	sInfo[8];	// contract class
	float	fMarginCost;	// margin cost at entering the trade
	float	fCommission;	// commission at entering the trade
	DWORD	flags2;		// internal flags
	int	nLotsTarget;	// original lots
	int	nAttempts;	// close attempts counter
	int	pad[1];
// saved until this position; change "TRD" header when changed
	void	*algo;		// trade ALGO 
	void	*manage;		// trade management function pointer
	var	*dSignals;	// pointer to advise parameters; uuid in live trading
	float fLastStop;	// for updating the stop
	float fPad[1]; 
	int	nBarLast;	// bar number of last trail step  
} TRADE;

#define TR_LONG		0
#define TR_SHORT		1			// short position
#define TR_OPEN		(1<<1)	// position is open
#define TR_EXTCLOSED	(1<<2)	// trade not found in the broker list
#define TR_EXPIRED	(1<<3)	// option or future expired
#define TR_WAITSELL	(1<<4)	// close position at the next tick
#define TR_WAITBUY	(1<<5)	// pending trade 
//#define TR_UNUSED	(1<<6)	// 
#define TR_SUSPEND	(1<<7)	// suspend trade function
#define TR_EVENT		(1<<8)	// trade function was called by enter/exit event
#define TR_MISSEDENTRY	(1<<10)	// missed the entry limit in the last bar
#define TR_MISSEDEXIT	(1<<11)	// missed the exit for some reason -> retry
#define TR_NOTFILLED	(1<<12)	// Trade not filled -> adapt limit and retry
#define TR_SIMULATED	(1<<12)	// Don't calculate result
#define TR_NONET		(1<<14)	// Don't open a net trade yet
#define TR_NET			(1<<15)	// Pool trade
#define TR_PHANTOM	(1<<16)	// Phantom trade 
#define TR_EXERCISE	(1<<17)	// exercise an option contract
#define TR_STOPPED	(1<<18)	// closed due to stop loss in the last bar, or a margin call
#define TR_PROFIT		(1<<19)	// closed due to profit target in the last bar
#define TR_TIME		(1<<20)	// closed due to timeout in the last bar
#define TR_SOLD		(1<<21)	// closed due to exit at market in the last bar
#define TR_CANCELLED	(1<<22)	// removed from trade list
#define TR_GTC			(1<<23)	// Good-till-cancelled trade on the broker side
#define TR_ACCOUNT	(1<<24)	// trade with the main account
#define TR_ENTRYSTOP	(1<<25)	// entry stop, rather than limit
#define TR_BSTOP	TR_ENTRYSTOP	// bracket stop order
#define TR_ENTER		(1<<26)  // entered by TMF return value
#define TR_EXIT		(1<<27)  // exit by TMF return value
#define TR_REMOVED	(1<<28)	// removed from the online trade list (f.i. margin call or manually closed)
#define TR_BAR			(1<<29)	// run TMF on any bar only, not any tick
#define TR_REVERSED	(1<<30)  // indicate exit by reversal

#define TR_AON			1			// TradeMode all-or-nothing
#define TR_FILLED		(1<<1)	// TradeMode, assume complete fill

///////////////////////////////////////////////////////////////
// algo specific parameters & statistics
typedef struct STATUS { 
	var	vSkippedMargin;	// margin accumulation of skipped trades
	var	vWin,vLoss;			// gross wins and losses
	var	vWinVal,vLossVal;	// value of open trades, test/trade mode only
	var	vReturn2;			// sum of squared returns
	var	vWinMax,vLossMax;	// largest win and loss
	var	vLossLotMax;		// largest loss per lot
	var	vWinStreakVal,vLossStreakVal;	// size of current win/loss streak
	int	numWin,numLoss;	// number of won and lost trades	
	int	nWinStreak,nLossStreak; // length of current win and loss streak
	int	numWinning,numLosing;	// number of winning and losing open trades, test/trade mode only
	DWORD	dwWin,dwLoss;		// WFO win/loss flags 
	DWORD	dwColorWin,dwColorLoss;	// trade colors in chart
// clear statistics until this position
	DWORD	flags;
	int	nModel;				// model number for prediction
	int	nComponent;			// component number
	DWORD	pad[1];
	var	vPad[4];
	var	Skill[NUM_SKILLS];	// general purpose variables
	var	Result[NUM_RESULTS];	// last 20 trade results
	char	sAlgo[NAMESIZE];	// algo identifier
// saved until this position
	var	vTrainPF;			// training profit factor
	var	vOptimalF;			// OptimalFLong / OptimalFShort
	var	vOptimalF2;			// OptimalF (short), R2 (long)
	var	vWFOProfit;			// profit of the current WFO cycle
	int	numPending;			// number of pending trades
	int	nBalance;			// net sign sum of advise objective
	int	numSignals;			// signals per rule
	DATASET*	History;				// signal history for rule learning
	void*	Rule;					// pointer to tree or perceptron function
// clear again until this position
	struct STATUS *other;	// opposite status (short<->long)					
	ASSET	*asset;				// asset pointer
	int	nCycles;				// number of optimize cycles
	int	nSteps[MAX_PARAMS];	// list of optimize steps
	float	fParam[MAX_PARAMS];	// list of optimal parameters
	float* fStat;				// matrix of optimize results
	var*	pCurve;				// component equity/balance curve
} STATUS;

// overall performance statistics (averaged over sample cycles)
typedef struct PERFORMANCE
{
	var	vWin,vLoss;			// gross wins and losses
	var	vPips;				// gross win-loss in pips
	var	vWinMax,vLossMax;	// largest win and loss
	var	vDrawDown;			// maximum balance-equity drawdown 
	var	vEquityDown;		// max equity drawdown
	var	vCommissionCost;	// accumulated negative commissions
	var	vPhantomWin,vPhantomLoss;	// win/loss by virtual trades
	var	vMarginMax;			// maximum margin 
	var	vRiskMax;			// maximum risk 
	var	vVolume;				// total trade volume
	var	vObjective;			// current objective() result 
	var	vR2;					// coefficient of determination
	var	vMean;				// average simple return per bar
	var	vStdDev;				// standard deviation of simple returns
	var	vUlcer;				// ulcer index; root of mean of squared drawdown percentages
	var	vRollCost;			// accumulated rollover costs
	var	vSlippageWin,vSlippageLoss;		// accumulated slippage costs
	var	vSpreadCost;		// accumulated spread costs
	var	vMarginAvg;			// average margin
	var	vCBI;					// current CBI value
	var	vInterestSum;		// accumulated interest
	int	numWin,numLoss;	// number of winning and losing trades 
	int	numWinStreakMax;	// max number of consecutive wins
	int	numLossStreakMax;	//. max number of consecutive losses
	int	numMarketBars;		// number of bars with active trading
	int	numDrawDownBars;	// number of bars in balance drawdown
	int	numMAEBars;			// number of bars in equity drawdown
	int	numDrawDownMax;	//. max drawdown bars
	int	numMarketWin,numMarketLoss;	// bars in market of winning/losing trades
	int	numMarketTotal;	// total number of bars in market
	int	numTradeBarsMax;	//. max length of trade
	var	vBalancePeak;		// current balance peak
	var	vEquityPeak,vEquityValley;	// current equity peak and subsequent valley
	var	vEquityDD;			// deepest equity valley
	var	vEquityValleyAfterBalance;	// lowest equity valley after balance peak
	var	vWinStreakVal,vLossStreakVal;	// size of current win/loss streak
	int	numTradesMax;		// max number of concurrent trades
	int	nWinStreak,nLossStreak;	// current number of consecutive wins / losses
	int	nBalancePeakBar;	//. bar numbers for drawdown
	int	nEquityPeakBar,nEquityValleyBar;	
	int	nDnMaxStart;		// bar number of the longest down time 
	int	nEquityValleyBalanceBar; //.
	DATE	tSessionEnd;		// time of session exit, for continuing statistics
	int	nSessionEndBar;	// bar number of the last bar
	int	nPad;
	var	vSemiDev;			// semideviation
} PERFORMANCE;

// global variables
typedef struct GLOBALS
{
// trade parameters (r/w)
	var	vLots;	// number of lots to buy; 1 lot = minimum order amount = vPIPCost/vPIP contracts
	var	vMargin;	// margin per trade; determines lots when nonzero
	var	vRisk;	// risk limit per trade; limits lots according to from vStop
	var	vCapital; // initial capital for reinvesting strategies
	var	vStop;	// stop loss - sell when the trade loses this amount 
	var	vTrail;	// adapt stop loss when the trade wins this amount 
	var	vTrailSlope;	// move stop loss by this percentage of current trade profit
	var	vTrailLock;	// lock this percentage of favorite excursion
	var	vTrailStep;	// move stop loss every bar by this percentage of price-stop distance
	var	vTakeProfit; // profit limit - sell when the trade goes your way by this amount 
	var	vEntry;	// order entry - buy when the price rises or falls by this amount 
	var	vOrderDelay;
	int	nExitTime;	// sell at market after this number of bars
	int	nEntryTime;	// wait this number of bars for entry limit orders
	
	int	nHedge;		// hedging mode
	int	nVerbose;	//. verbosity level
	int	nBoxState;	// external message box state
	int	nLifeTime;	// trade duration in bars			
	int	nGapDays;		// gap tolerance
	int	nDataHorizon;	//. WFO horizon in bars

	var	vSlippage;  // simulated order execution delay in seconds (default = 0.5)
	var	vBarPeriod;	// bar period in minutes, fractional
	var	vRound;		// rounding factor, i.e 0.1 = round to the first decimal
	var	vFuzzyRange;	// for fuzzy logic
	var	vFuzzyLevel;	// for defuzzy
	var	vAdvise[2];		// advise parameters
	var	vMCDrawDown;	// Drawdown at confidence level

	int	nMonteCarlo;	// Monte Carlo iterations
	int	nConfidence;	// Monte Carlo confidence level
	long	pad1[10];

	var	vStopFactor;	// for sending the stop to the broker
	var	vOrderLimit;	// for sending limit orders to the broker
	var	vTrailSpeed;	// trail weight factor in percent
	var	vAssetFactor,vAssetOffset;
	int	numCores;		// multi-core training
	int	nCore;			// current core, 1..numCores
	int	nSelectCore;	// select a core for multithreaded cycles
	int	nTrainMode;		// optimize mode
	int	nFill;			//. order fill mode
	int	nTickSize;		// T6 or THL, for storing internal ticks
	int	nMinutesPerDay;	// minimum trading time per day, default = 360
	DATE	tNow;				// for time/date functions
	var	vSpreadFactor;	// 0.5 = open at mid price
	int	nStartMarket,nEndMarket; // market hours
	int	nMaxLong,nMaxShort;	//. limits to number of long/short trades
	int	nLogNumber;		// append this number to log files.
	int	nTradeMode;		// TR_BROKER2,TR_PHANTOM
	int	cAccountCCY;	//. account currency character
	int	nAccountDecimals;	// number of decimals for account values
	var	vCBIScale;		// scale factor for CBI depth
	var	vStopPool;		// stop factor for pool trades 
	var	vAmount;			// trade volume; 100000 contracts for currencies, 1 contract for anything else
	var	vMaxRequests;	// limits of the broker API
	var	vOrderDuration;	// of a GTC order
	int	nComboLeg;		// Number of the current combo leg, 1..4
	COMBO	*combo;			// current selected combo
	var	vScholzBrake;	// Olaf Scholz tax limit
	var	vPad2;			// 
	long	pad2[4];

// simulation performance (r/o)
	STATUS	*statLong,*statShort;	// component statistics, set up by asset() and algo()
	PERFORMANCE	w;			// overall win and loss statistics
	int	pad20[8];

	DATE	tStartTime;		// session start time
	DATE	tDayOffset;		// for simulating live trading on a different day
	DATE	tTimestamp;		// of last price quote
	DATE	tTimeNext;		// next bar increase		
	DATE	tTimeStart;		// latest history start of all assets
	var	vInitialBalance;
	var	vBarRange;		// sum of all price movements
	int	nHistoryTicks;	// number of ticks for BrokerHistory2
	int	nPriceEvent;	// Outlier (1) or Split (2..10)
	int	nAssets;			// number of used assets
	int	nLocks;			//. number of locks
	DWORD	nUniqueNumber;	// for generating unique file names
	int	nHistoryZone;	// convert local time in history downloads
	int	nBrokerZone;	// convert local time in broker plugin
	int	numTicks;		// total historical ticks processed
	int	pad3[6];

// account parameters (r/o)
	var	vLossGlobal;	// total loss of all instances
	var	vInterest;	// interest on margin
	var	vMarginVal; // total margin required for all open positions on the account
	var	vMarginSum; // total margin required for all open positions of the strategy
	var	vRiskSum;	// total risk of all open positions
	var	vWinVal,vLossVal;	// current win/loss of all open positions
	var	vBalance;	// account balance in trade mode
	var	vEquity;		// account balance plus open trade value in trade mode
	int	numTrades;	// number of open or pending trades
	int	numPending;	// number of virtual or real pending trades
	int	numShort,numLong;	//. number of open long or short positions
	int	numWinning,numLosing,numEven;	// # of trades winning, losing, break even
	int	numWFOWin,numWFOLoss;	//. number of won or lost WFO cycles
	long	pad4[8];

// simulation/optimization parameters (r/w)
	int	nBarZone;		// DST zone for local time bars
	int	nBarOffset;	// bar period offset in minutes
	int	nTimeFrame;	// time frame for price() and series() in number of bars
	int	nFrameOffset;	//. timeframe offset in bars
	int	numTotalCycles;	// number of complete cycles
	int	numSampleCycles;	// number of oversampling cycles 
	int	numOptCycles;	// number of parameter optimize runs
	int	numWFOCycles;	//. number of WFO runs
	int	numYears;	// number of years of the simulation (default = 0 = all years up to last year)
	int	numDays;		// number of days of the simulation (default = 0 = all)
	int	nStartDate;	// simulation start year (yyyy) or exact start date (yyyymmdd] (default = 2010)
	int	nEndDate;	//. simulation end date (yyyymmdd] (default = current year)
	int	nStartWeek,nEndWeek;		// Week start and end day & hour
	int	nUpdateDays;	// automatically update history when older than given number of days (default: 60)
	int	nMaxBars;	//. the maximum number of bars to simulate
	int	nUnstablePeriod;	// number of lookback bars added for exponential indicators (default = 40)
	int	nLookBack;	// number of bars before the simulation starts (automatically adjusted)
	int	nDataSplit;	// Percentage of in sample data (f.i. 90 for 90% in sample, 10% out of sample)
	int	nDataSkip;	//. Bars to skip with the SKIP1..3 flag
	int	nDetrend;	// 1 = detrend trade results; 2 = detrend price functions; 4 = detrend price curve
	int	nWeekend;	// weekend behavior, deprecated
	int	nTradesPerBar;	// max trades / numbars
	int	nAttempts;		//. download attempts
	var	vDataSlope;	// 1..3, bias factor for giving more weight to the last trades
	var	vDataWeight; // automatically set, 3 or 1.5 for one-week and two-week data sets
	var	dOptFactor[2]; // Optimize factors at range borders
	var	vOptimalFRatio; // 0 or 2..10, ratio of maximum to minimum OptimalF
	var	vOutlier;		// Outlier detection
	float fWeight;		// current weight factor
	int	nTimeStep;	// last time frame
	int	nWFOPeriod;	// length of the WFO period
	int	nBarMode;	//. bar generating method
	int	nDay;			// current simulation day (after lookback)
	int	numAllocDays;	// maximum number of days in the simulation
	int	nReTrainDays;	// re-training interval
	int	nTickTime;	//. minimum tick time in milliseconds (default = 100)
	int	nTickAvg;	// Price smoothing on incoming prices
	int	nTimeFix;	// ms, add this to historical price quotes
	int	nTockTime;		// Minimum tock time in milliseconds (default = 60000);
	int	nExpiryTime;	//. UTC HHMM, time of day for contract expiration
	int	nCommand[4];	//. command line numbers
	int	nTradeRate;		// BrokerTrade update rate
	long	pad5[7];

	var	vSlider[4]; // current values from the sliders, in the range defined by slider()
	int	nProgress1,nProgress2;	// progress bar
	string sInfo;						// info window
	CONTRACT *contract;	//. selected contract or combo

// simulation state (r/o)
	int	nFirstBar;	// first bar that lies at or after g->nStartDate
	int	numBars;		// total number of bars of the simulation, depends on nBarPeriod
	int	numAllocBars;	// size of the bar, plot, and price arrays
	int	numMinutes;	//. total minutes of the test frame	
	int	nTick;		// current tick number in trade management functions
	int	nBar;			// current bar number
	int	nTotalCycle;	// current cycle
	int	nSampleCycle;	//. current oversampling cycle number	
	int	nParLoop;	// current optimize call number within one loop
	int	nParTotal;	// current optimize call number of all loops
	int	numParTrain;	// number of parameters trained per loop
	int	nStepCycle;	//. current optimize step
	int	nParCycle;	// current parameter optimizing run, 1..numParTrain
	int	nOptCycle;	// optimization sub-cycle
	int	nWFOCycle;	// current WFO cycle
	int	nFrameStart;	//. start bar of the active data frame
	int	numFrameBars;	// size of the active data frame in bars
	int	numLoops[2];	// total number of loops in training mode
	int	nLoop[2];		//.. current loop argument number (starting with 1)
	int	nLoopCycle[2];	// trained loop argument number, or 0 for whole loop
	void*	pLoopPar[2];	//.. current loop parameter
	int	nSelectWFO;		// WFO cycle to select, or 0 for all cycles
	int	nLogCycle;		// Log trades of a certain train cycle; format WLLPS (Walk Loop0 Loop1 Par Step)
	BOOL	bDoStep,bDoLoop;	//.. TRUE during optimization
	int	numAssets;		// number of assets used in the script
	var	vParameter;		//. current optimize value
	var	vObjectiveBest;	// best result from objective()
	int	nLoopSelect[2];	// select single argument from loop
	int	nWFOStart;		// bar number of the current WFO cycle start
	int	nTrainFrame,nTestFrame;		// size of the training/test period in bars
	int	nModels;			//. number of models for prediction
	int	nUserBar;		// return value from bar() function
	int	nItor;			// counter of a for(trade) loop
	int	numPhantom;		// number of phantom trades
	int	numRejected;	//. number of rejected trades
	int	nComponents;	// component counter
	int	nFrameEnd;		// last bar of the current frame
	int	nOrderRow;		// row number in order list
	int	nSeries;			// current series number
	long	pad62[8];

	var	*pSeriesBuffer;	// pointer of the last/next series
	var	*pPrevCurve;	// daily balance/equity curve from previous backtest
	long	nPrevLength;	// length of the balance/equity curve
	T6		*pTick;			// current tick for TMF and tick functions
	int	nLastPeriod;	// last time period passed to an indicator
	var	*pLastSeries;	// last series passed to an indicator
	var	*pTime;		// daily date 
	var	*pCurve;		// daily balance/equity curve from
	long	RHandle;		// handle of the R Bridge
	string sParameters; // content of the parameter file
	string sFactors;	// content of the OptimalF factor file
	string sRules;		// content of the rule file
	var	*pParTotal;	// parameter values of all components
	var	*pParLoop;	// parameter values of current component
	void	*pRules;		// compiled advise rules

	TRADE	*tr;			// current trade in trade function or enumeration
	ASSET	*asset;		// current asset, set up by asset()
	BAR	*bars;		// list of bars
	float	*pResults;	// array of bar results
	var	*pEquity;	// displayed equity curve
	var	*pDrawDown;	// displayed drawdown curve
	var	*pMonteCarlo;	// Monte Carlo simulation results

	const char *sAlgo;		// current algorithm identifier, set up by algo()
	const char *sScript;	// current script name, used for .par/.fac/.c/.csv
	string sExeName;	// current name for the .x file to compile
	string sAssetList;	// file name of current assets list
	string sCSVLogName;	// CSV log file path for storing trade results
	const char *sBroker;	// name returned by the broker plugin
	const char *sHistory;	// extension of the history files
	string sWebFolder;	// HTML page folder
	string sFactorList;	// factor file name
	const char *sZorroFolder;	// Zorro's own folder
	const char *sRTermPath;	// path to the R terminal
	string sCurves;	// file name for daily balance curves
	string *pAssets;	// list of asset names
	string sMessage;	// last critical message f.i. for possible orphans
	string sAccount;	// Account number from the scrollbox
	string sContractSymbol;		// selected option or future underlying
	string sButton;	// Text for the Result button
	const char *sError;		// Error string for identifying code positions
	string sAssetBox; // Asset name from the scrollbox
	const char *sDefine;	// -d name from the command line
	int*	nHolidays;	// holiday list
	const char *sAccountName;	// from the account list
	var*	pShape;		// price curve bending array
	PARAMETER* pParameters;	// list of parameters in a training run
	long	pad7[13];

// chart/log parameters (r/w)
	int	nPlotLabels; // # of x axis labels to skip in histograms
	int	nPlotScale;	// width of a bar in the chart image, in pixels (default = 4; 0 for no chart)
	int	nPlotWidth;	// maximum main chart width in pixels
	int	nPlotHeight1,nPlotHeight2;	// Main chart and additional chart height in pixels
	int	nPlotDate;	// start date of the plot (default = 0 = plot all)
	int	nPlotBars;	// number of bars to plot (default = 0 = all)
	DWORD	dwColorCandle;
	DWORD dwColorUp,dwColorDn;	// color of white / black candles
	DWORD	dwColorEquity,dwColorDD;
	DWORD	dwColorWin,dwColorLoss;
	string sPlotLabelFormat;
	int	nPlotBorder;
	DWORD	dwColorBars[3];
	DWORD	dwColorPanel[6];
	int	nPlotPeriod;	// Chart update period in minutes
	int	nPlotMode;
	int	nPlotStart;		// start bar of the plot
	int	nTimePerBar;	// playback speed, ms per bar

	int	nPopulation;	// for genetic optimization 
	int	nGenerations;
	int	nMutationRate;
	int	nCrossoverRate;
	int	nSampleOffset;	// sample cycle offset in bars
	int	nPlotText;		// Text zoom threshold
	int	nExitCode;		// Exit code
	long	pad8[8];

	DWORD	nPin;
	DWORD	nSaveMode;	// load/save flags
	DWORD	dwBrokerPatch;	// work around API bugs
	DWORD	dwMode;		// mode switches
	DWORD dwStatus;	// status flags
	int	nState;		// training machine state
	DWORD	flags;		// internal flags
	int	nFuncId;		// identifier for function list
	DWORD* Functions;	// null terminated function list
	HINSTANCE RLib;	// R DLL Handle
	ASSET* BarAsset;	// First asset that was used for bar generation
	HWND	hWnd;			// Zorro's Window handle
	int	nPriceType;	// current price type, 4 = suppress requests
	ASSET* PrevAsset;	// Global asset in a trade loop
	DWORD	flags2;		// more internal flags
	DWORD	dwFlags2;	// more mode switches
	DWORD	flags3;		// more internal flags
	var	vTemp;		// for macros
	long	pad9[6];

// Indicator return variables
	var vAroonDown,vAroonUp;
	var vRealUpperBand,vRealMiddleBand,vRealLowerBand;
	var vInPhase,vQuadrature;
	var vSine,vLeadSine;
	var vMACD,vSignal,vMACDHist;
	var vMAMA,vFAMA;
	var vMin,vMax;
	var vMinIdx,vMaxIdx;
	var vSlowK,vSlowD,vFastK,vFastD;
	var vDominantPeriod,vDominantPhase;
	var vRed,vGreen,vBlue;
	var vError;
	var vEMA;
	var vPeak,vSlope,vSign,vLength;
	var vMean;
	var vMomentum;
	var vTenkan,vKijun,vSenkouA,vSenkouB;
	var vTest;
	int nHHBar,nLLBar;
	long	pad10[10];

} GLOBALS;

//////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define SCRIPT_VERSION	2310
#else
#define SCRIPT_VERSION	262
#endif
#ifndef NO_DEFINES

// mode switches
#define SKIP1		(1<<0)	// skip 1st of every 3 weeks
#define SKIP2		(1<<1)	// skip 2nd of every 3 weeks
#define SKIP3		(1<<2)	// skip 3rd of every 3 weeks
#define BINARY		(1<<3)	// trade binary options - also for optionVal
#define PRELOAD	(1<<4)	// load prices from historical data
//#define TRAINMODE	(1<<5)	// enforce [Train] mode
#define MAECAPITAL	(1<<6)	// consider MAE when calculating capital and annual return
#define PLOTNOW	(1<<7)	// create a chart automatically after test
#define LOGFILE	(1<<8)	// store log file - also for assetHistory
#define LEANER		(1<<9)	// don't use OHLP data, only pClose
#define LEAN		(1<<10)	// don't use volume & spread data
#define EXE			(1<<11)	// generate EXE (Zorro S)
#define RULES		(1<<12)	// generate/use advise rules
#define FACTORS	(1<<13)	// generate reinvestment factors
#define PARAMETERS (1<<14)	// generate/use strategy parameters
#define OPENEND	(1<<15)	// ignore open trades at the end of the test
#define PEEK		(1<<16)	// allow peeking into the future
#define RISKLIMIT	(1<<17)	// don't trade when trade risk > 2*Risk
#define MARGINLIMIT (1<<18) // don't trade when real margin > 2*calculated margin, or when total margin left < 1000
#define ACCUMULATE (1<<19)	// accumulate Margin for skipped trades
#define TESTNOW	(1<<20)	// run a test automatically after training
#define RECALCULATE (1<<21) // recreate series after parameter loading
#define COMMONSTART (1<<22) // delay start until all assets are available 
#define NOLOCK		(1<<23)	// don't sychronize API access
#define FAST		(1<<24)	// ticks in FAST mode - also for advise()
#define NFA			(1<<25)	// NFA compliant account: no "hard" stop loss, no hedging, no position closing
#define NF			(1<<26)	// for all new flags
#define TICKS		(1<<27)	// simulate trades every tick (slow)
#define BALANCE	(1<<28)	// store and display balance rather than equity curves
#define STEPWISE	(1<<29)	// stepwise debugging
#define ALLCYCLES	(1<<30)	// sum up statistics over all sample cycles (TrainMode: separate .fsc for all cycles)
#define OFF			(1<<31)	// switch flag off

// status flags
#define TRADED		(NF|(1<<0))	// trades have been opened
#define CHANGED	(NF|(1<<1))	// script or asset was changed -> init strategy sliders
#define INITRUN	(NF|(1<<2))	// init run before the first bar, for initialization
#define EXITRUN	(NF|(1<<3))	// last bar, all trades are closed, for result calculation
#define TESTMODE	(NF|(1<<4))	// [Test] mode
#define TRAINMODE	(NF|(1<<5))	// [Train] mode; also for print()
#define TRADEMODE	(NF|(1<<6))	// [Trade] mode
#define DEMO		(NF|(1<<7))	// Running on demo account
#define LOOKBACK	(NF|(1<<8))	// Lookback period, no trading
#define FIRSTRUN	(NF|(1<<9))	// First run with valid price data, usually on bar 1
#define COMMAND	(NF|(1<<10))	// Zorro started from the command line
#define COMPILED	(NF|(1<<11))		// script is executable (*.x)
#define RULCYCLE	(NF|(1<<12))		// generate advise rules
#define FACCYCLE	(NF|(1<<13))	// generate reinvestment factors
#define PARCYCLE	(NF|(1<<14))		// generate strategy parameters
#define CONTRACTS	(NF|(1<<15))	// contracts are traded
#define PORTFOLIO	(NF|(1<<16))	// assetList() or loop() function called
#define ASSETS		(NF|(1<<17))	// asset() function called
#define SELECTED	(NF|(1<<18))	// asset is same as [Asset] Scrollbox (not in loops)
#define PLOTSTATS	(NF|(1<<19))	// plot histogram rather than price chart
//#define FLAG(N)	(NF|(1<<20)|(N<<4))
#define SPECIALBAR (NF|(1<<21))	// user-defined bar length
#define MARGINCALL (NF|(1<<22))	// Margin + Loss exceeds Capital
#define NEWDAY		(NF|(1<<23))	// Day change after last bar 
#define PROCESS	(NF|(1<<24))	// ReTrain or ReTest
#define SPONSORED	(NF|(1<<25))	// Zorro S version
//#define NF			(1<<26)
#define FIRSTINITRUN (NF|(1<<27))	// Very first run in a multi-cycle script.
#define SHORTED	(NF|(1<<28))	// Short trades have been opened
#define AFFIRMED	(NF|(1<<29))	// [Ok] clicked on nonmodal message box -> ZorroDLL.cpp
#define RUNNING	(NF|(1<<30))	// Simulation is running

#define FLAG(N)		(NF|(1<<20)|(N<<4))	// new type flag
#define SCREENSAVER	FLAG(1)	// don't suspend power management 
#define CACHE			FLAG(2)	// use cache for unlimited asset history
#define BUSY			FLAG(3)	// broker API or script function busy 
#define SLIDERS		FLAG(4)	// slider was moved
#define NOWATCH		FLAG(5)	// ignore watch() statements
#define NOSHIFT		FLAG(6)	// prevent shifting series

// defines for functions and parameters
#define NOW		-999999
#define NAY		-999997
#define NAIVE		0
#define ATCLOSE	1
#define DELAYED	3
#define HFT			8
#define DIAG		8
#define ALERT		(1<<4)
#define SILENT		(1<<5)
#define LOGMSG		(1<<9)	// show log in message window

#define NEURAL		(1<<20)	// use external AI
#define DTREE		(1<<21)	// use a decision tree
#define PERCEPTRON (1<<22)	// use a perceptron
#define PATTERN	(1<<23)	// use pattern match
//#define FAST		(1<<24)	// match fast
#define FUZZY		(1<<25)	// match fuzzy
#define SIGNALS	(1<<26)	// export signals + objective to .csv
#define BALANCED	(1<<28)	// balance positive and negative results
#define RETURNS	(1<<29)	// use trade returns

#define NEURAL_INIT		(1<<20)	// neural function modes
#define NEURAL_EXIT		(2<<20)
#define NEURAL_LEARN		(4<<20)
#define NEURAL_TRAIN		(5<<20)
#define NEURAL_PREDICT	(8<<20)
#define NEURAL_SAVE		(16<<20)
#define NEURAL_LOAD		(17<<20)

#define VOLATILE 		(1<<6)
#define OVERRIDE		(1<<7)
#define GET_SPREAD	(1<<8)
#define UNADJUSTED	(1<<9)
#define FOR_ASSET		(1<<10)
#define IMMEDIATE		(1<<11)
#define FROM_YAHOO	(1<<12)
#define FROM_QUANDL	(1<<13)
#define FROM_GOOGLE	(1<<14)
#define FROM_AV		(1<<15)
#define FROM_STOOQ	(1<<16)
#define FROM_QTABLE	(1<<17)
#define FROM_BITTREX	(1<<18)
#define FROM_CRYPTOC	(1<<19)
#define FROM_IEX		(1<<20)
#define FROM_SOURCE	(1<<21)

#define FOREX		1
#define INDEX		2	
//#define STOCK	3 

#define TRADES		(1<<0)	// Detrend, randomize, predict, TrainMode etc
#define PRICES		(1<<1) 
#define CURVE		(1<<2)
#define DETREND	(1<<2)
#define INVERT		(1<<3)
#define NOPRICE	(1<<4)
#define SHUFFLE	(1<<5)
#define BOOTSTRAP	(1<<6)
#define RECIPROCAL (1<<7)
#define RANDOMWALK (1<<8)
#define SHAPE		(1<<9)
#define PHANTOM	(1<<16)
#define PARABOLIC	(1<<20)
#define CROSSOVER	(1<<21)
#define PEAK		(1<<22) // also for TrainMode
#define VALLEY		(1<<23)
#define ASCENT		(1<<24)	// use plateau seeking optimization
#define GENETIC	(1<<25)	// use genetic optimization
#define BRUTE		(1<<26)	// use brute force optimization
#define SETFACTORS (1<<27)	// store script-set factors
//#define ALLCYCLES	(1<<30)	// Factor generation per cycle

#define UTC		24	// Coordinated Universal Time
#define WET		0	// Western European Time (London)
#define CET		1	// European time zone (Frankfurt)
#define ET		-5	// Eastern Time (New York)
#define EST		-5	// Eastern Time (New York)
#define CST		-6	// Central Time (Chicago)
#define JST		UTC+9	// Japan Standard Time (Tokyo)
#define AEST	10	// Australian Eastern Standard Time (Sydney)

#define MONDAY		1
#define TUESDAY	2
#define WEDNESDAY	3
#define THURSDAY	4
#define FRIDAY		5
#define SATURDAY	6
#define SUNDAY		7

#define NEW		(1<<0)	// begin new chart
#define BARS	(1<<1)	// bars instead of curves
#define BAND1	(1<<2)	// upper band
#define BAND2	(BAND1+1)	// lower band
#define MAIN	(1<<3)	// print in main window
#define STATS	(1<<4)	// print histogram
#define AXIS2	(1<<5)	// plot on 2nd axis
#define SUM		(1<<6)	// add values; fill skipped bars
#define AVG		(1<<7)	// calculate average
#define LOG		(1<<8)	// use logarithmic scale
#define DEV		(1<<9)	// calculate standard deviation
#define NRM		(1<<10)	// normalize to 1
#define MINV	(1<<12)	// plot the bar minimum
#define MAXV	(1<<13)	// plot the bar maximum
#define DEL		(1<<14)	// delete the previous plot and start over
#define LBL2	(1<<15)	// label only even bars
#define GRAPH	(1<<16)	// plot line/dot graph
#define LINE	(1<<17)	// plot a straight line
#define END		(1<<18)	// line end point
#define DOT		(1<<19)	// plot a colored symbol
#define SQUARE	(DOT+(1<<20))
#define DIAMOND (DOT+(2<<20))
#define TRIANGLE (DOT+(3<<20))
#define TRIANGLE2 (DOT+(4<<20))
#define TRIANGLE3 (DOT+(5<<20))
#define TRIANGLE4 (DOT+(6<<20))
#define CROSS	(DOT+(8<<20))
#define CROSS2	(DOT+(9<<20))
#define ALL		(1<<24)
#define TXT		(1<<25)
#define MULTICOLOR (1<<30)

#define PL_ALL		(1<<6)
#define PL_LONG	(1<<7)
#define PL_FINE	(1<<8)
#define PL_ALLTRADES (1<<9)
#define PL_DIFF	(1<<10)
#define PL_FILE	(1<<11)
#define PL_BENCHMARK	(1<<12)
#define PL_TITLE	(1<<13)

#define RED			0xff0000
#define GREEN		0x00ff00
#define BLUE		0x0000ff
#define CYAN		0x00ffff
#define DARKBLUE	0x0000a0
#define LIGHTBLUE	0xadd8e6
#define PURPLE		0x800080
#define YELLOW		0xffff00
#define MAGENTA	0xff00ff
#define ORANGE		0xffa500
#define DARKGREEN	0x008000
#define OLIVE		0x808000
#define MAROON		0x800000
#define SILVER		0xc0c0c0
#define GREY		0x808080
#define BLACK		0x010101
#define WHITE		0xffffff
#define TRANSP		0x80000000

#define TO_WINDOW	1	// print channels
#define TO_LOG		2
#define TO_DIAG	3
#define TO_REPORT	4
#define TO_HTML	5
#define TO_FILE	6
#define TO_CSV		10
#define TO_CSVHDR	11
#define TO_ALERT	13
#define TO_TITLE	16
#define TO_INFO	17
#define TO_PANEL	18
#define TO_CHART	19
#define TO_ANY		(TO_WINDOW|TRAINMODE)

#define SV_TRADES		(1<<0)	// SaveMode
#define SV_SLIDERS	(1<<1)
#define SV_ALGOVARS	(1<<2)
#define SV_ALGOVARS2	(1<<3)
#define SV_STATS		(1<<4)
#define SV_BACKUP		(1<<8)
#define SV_HTML		(1<<9)

#define BR_FLAT		(1<<0)	// BarMode
#define BR_WEEKEND	(1<<1)
#define BR_MARKET		(1<<2)
#define BR_LEISURE	(1<<4)
#define BR_SLEEP		(1<<5)
#define BR_LOGOFF		(1<<6)

#define GET_TIME			5	// brokerCommand, last incoming tick time
#define GET_DIGITS		12	// Count of digits after decimal point 
#define GET_STOPLEVEL	14	// Stop level in points.
#define GET_STARTING		20	// Market starting date (usually used for futures).
#define GET_EXPIRATION	21	// Market expiration date (usually used for futures).
#define GET_TRADEALLOWED 22	// Trade is allowed for the symbol.
#define GET_MINLOT		23	// Minimum permitted amount of a lot.
#define GET_LOTSTEP		24	// Step for changing lots.
#define GET_MAXLOT		25	// Maximum permitted amount of a lot.
#define GET_MARGININIT	29	// Initial margin requirements for 1 lot.
#define GET_MARGINMAINTAIN	30	// Margin to maintain open positions calculated for 1 lot.
#define GET_MARGINHEDGED	31	// Hedged margin calculated for 1 lot.
#define GET_MARGINREQUIRED	32	// Free margin required to open 1 lot for buying.
#define GET_BROKERZONE	40	// time zone returned by broker plugin
#define GET_DELAY			41
#define GET_WAIT			42
#define GET_MAXTICKS		43 // max history ticks
#define GET_IDTYPE		44 // trade id, 0 = number, 1 = GUID string pointer
#define GET_MAXREQUESTS	45 // for setting up MaxRequests
#define GET_LOCK			46	// Locking required. 
#define GET_TYPE			50	// Asset type. 
#define GET_COMPLIANCE	51 // NFA compliance.
#define GET_NTRADES		52 // Number of open trades
#define GET_POSITION		53	// Open net lots per asset 
#define GET_ACCOUNT		54	// Account number (string)
#define GET_AVGENTRY		55	// Average entry price 
#define GET_BOOK			62	// Order book
#define GET_OPTIONS		64 // Option chain
#define GET_FUTURES		65	
#define GET_FOP			66	
#define GET_UNDERLYING	67	
#define GET_SERVERSTATE	68
#define GET_GREEKS		69 // for the last option price request
#define GET_LOOPS			70	// return # of wait loops of last command, for diagnostics 
#define GET_TRADES		71 // list of positions
#define GET_DATA			72 // direct response from REST API

#define SET_PATCH			128 // Work around broker API bugs
#define SET_SLIPPAGE		129 // Max adverse slippage for orders
#define SET_MAGIC			130 // Magic number for trades
#define SET_ORDERTEXT	131 // Order comment for trades
#define SET_SYMBOL		132 // set asset symbol for subsequent commands
#define SET_MULTIPLIER	133 // set option/future multiplier filter
#define SET_CLASS			134 // set trading class filter
#define SET_LIMIT			135 // set limit price for entry limit orders
#define SET_HISTORY		136 // set file name for direct history download
#define SET_COMBO_LEGS	137 // declare the next n trades as an option combo
#define SET_DIAGNOSTICS	138 // activate plugin diagnostics output
#define SET_AMOUNT		139 // set lot amount
#define SET_LEVERAGE		140 // set leverage for subsequent trades
#define GET_PRICETYPE	150 // type of prices returned by the API
#define SET_PRICETYPE	151 
#define GET_VOLTYPE		152 // type of volume returned by the API
#define SET_VOLTYPE		153 
#define GET_UUID			154 // uuid of last trade	
#define SET_UUID			155 // uuid for next trade
#define SET_ORDERTYPE	157 // 0 = fill-or-kill, 1 = immediate-or-cancel, 2 = good-till-cancelled 
#define SET_DELAY			169
#define SET_WAIT			170
#define SET_LOCK			171
#define SET_HWND			172
#define SET_MAXTICKS		173 // max history ticks
#define GET_CALLBACK		174 // plugin supplied callback function 
#define SET_COMMENT		180 // Comment on the chart window
#define SET_BROKER		181 // Set broker/exchange for aggregators
#define SET_SERVER		182 // Send ':' content of Server field
#define SET_CCY			183 // Send currency from CCY field

#define PLOT_STRING		188	// send a string to a plot object
#define PLOT_REMOVE		260
#define PLOT_REMOVEALL	261
#define PLOT_HLINE		280	// plot to the MT4 chart window
#define PLOT_TEXT			281
#define PLOT_MOVE			282

#define DO_EXERCISE		300	// exercise an option
#define DO_CANCEL			301	// cancel a GTC order

#define CALL			1	// options
#define PUT				2
#define EUROPEAN		(1<<2)
//#define BINARY	8	// shared with MODE()
#define FUTURE			(1<<5)
#define ONLYMATCH		(1<<6)	// select only contracts that exactly match the parameters 
#define ONLYW3			(1<<7)	// select only contracts in 3rd week
#define ASDISTANCE	(1<<8)	// select by strike distance to underlying
#define COMBOLEG		(7<<9)	// combo leg number, 1..4, 3 bit
#define OPTION			(CALL|PUT|EUROPEAN|BINARY)

#define MAType_SMA	0	// Types of Moving Average
#define MAType_EMA	1
#define MAType_WMA	2
#define MAType_DEMA	3
#define MAType_TEMA	4
#define MAType_TRIMA 5
#define MAType_KAMA	6
#define MAType_MAMA	7
#define MAType_T3		8

#define H_HISTORY		1001	// predefined handles
#define H_YIELD		1002
#define H_QUOTES		1003
#define H_HISTORY1	1004	
#define H_ASSET		1010	// + number of assets

#endif // NO_DEFINES
/////////////////////////////////////////////////////////
#endif
