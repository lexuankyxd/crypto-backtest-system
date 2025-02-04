## Config

Your config file should contains 3 parts: run mode, run config and strategy config. It should look something like this:

```json
{
  "mode_config": {
    "mode": "backtest"
    "market": "spot"
    // structure is mode dependent
  },

  "strategy": {
    "name": "demo"
  },

  "run_config": {
    "live_print": true,
    "live_print_interval": 60,
    "gen_report": true
  }
}
```

Mode config contains setting about the program's mode of operation. There are 3 mode, **backtest**, **live** and **paper**. Each mode has it's own config structure inside the **mode_config**.

### **Backtest mode config structure**

Suppose that you want to backtest your algorithm, you can either provide the backtesting data or provide the backtesting pair, time period in the config and let the program download it.

The config below is for downloaded data, i.e. user provided.

```json
{
  "mode_config": {
    "mode": "backtest",
    "market": "spot",
    "download_data": false,
    "data": [
      { "type": "kline", "dir": "path/to/data" },
      { "type": "agg_trade", "dir": "path/to/data" },
      { "type": "trade", "dir": "path/to/data" }
    ]
  }
}
```

Config for downloading data.

```json
{
  "mode_config": {
    "mode": "backtest",
    "market": "spot",
    "download_data": true,
    "data": [
      {
        "type": "kline",
        "symbol": [{ "pair": "BTCUSDT" }, { "pair": "BNBUSDT" }],
        "time": { "start": "12/12/2024", "end": "31/12/2024" }
      }
    ]
  }
}
```

Data will be downloaded from [Binance](https://data.binance.vision/)
