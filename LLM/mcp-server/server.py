# server.py
from mcp.server.fastmcp import FastMCP
import math
from typing import Optional

import yfinance as yf
from my_var.var import calculate_returns, calculate_var_cvar_historical
from my_var.utils import extract_column_from_csv

import warnings
import pandas as pd
from datetime import datetime
warnings.filterwarnings('ignore')

# Create an MCP server
mcp = FastMCP("Quant-MCP-server")

@mcp.tool()
def extract_column_from_csv_mcp(csv_path: str, column: str, days: int, round:int=4) -> list[float]:
    """
    Extract the last N values from a specified column in a CSV file containing historical prices.

    Parameters:
    csv_path: str, absolute path to the CSV file
    column: str, column name to extract values from
    days: int, number of last days to extract

    Returns:
    list: last N values from the specified column

    input example:
    {
        "csv_path": "/path/to/prices.csv",
        "column": "Close",
        "days": 252,
        "round": 4
    }

    output example:
    [3, 1.02, 1.05, 1.05, 1.02, 1.03, 1.05, 1.02, 1.02, 0.9864, 1.04, 0.98, 0.88, 0.9531, 0.9644, 0.8967, 0.9061, 1.05, 1.07, 0.9987, 0.9491, 0.96, 0.992, 1.04, 1.04, 1.08, 1.02, 1.08, 1.19, 1.28, 1.17, 1.09, 1.04, 1.05, 1.12, 1.02, 1.04, 1.07, 1.03, 0.9904, 1.03, 0.948, 0.8972, 0.7961, 0.8462, 0.7778, 0.8305, 0.7902, 0.8537, 0.8966, 0.8409, 0.8856, 0.8982, 0.87, 0.836, 0.9275, 0.9068, 0.9659, 0.9459, 0.91, 0.8599, 0.8807, 0.9164, 0.8312, 0.835, 0.8, 0.7536, 0.6881, 0.7336, 0.8044, 0.8202, 0.8526, 0.8216, 0.8404, 0.82, 0.8151, 0.7939, 0.765, 0.76, 0.7402, 0.7781, 0.8102, 0.7831, 0.753, 0.7644, 0.748, 0.7849, 0.7847, 0.7789, 0.7659, 0.7555, 0.8164, 0.8422, 0.8105, 0.92, 0.951, 1.11, 1.28, 1.23, 1.21, 1.2, 1.22, 1.5, 1.46, 1.41, 1.32, 1.23, 1.13, 1.12, 1.2, 1.43, 1.51, 1.52, 1.49, 1.7, 1.55, 1.41, 1.3, 1.31, 1.35, 1.48, 1.74, 2.75, 2.2, 2.4, 3.05, 3.02, 3.14, 3.11, 3.18, 4.38, 4.47, 6.49, 7.38, 5.97, 7.16, 8.43, 11.13, 10.69, 7.47, 9.37, 10.96, 11.35, 15.44, 17.08, 17.0, 15.26, 20.0, 19.02, 19.51, 18.39, 10.04, 8.93, 6.05, 8.95, 10.94, 11.24, 9.83, 13.98, 13.91, 13.47, 13.2, 12.45, 13.08, 12.66, 12.3, 13.17, 13.47, 13.72, 13.83, 13.29, 12.85, 12.35, 11.02, 11.75, 12.25, 11.81, 10.52, 11.03, 11.47, 10.75, 10.12, 9.03, 9.28, 8.03, 8.46, 7.7, 7.86, 8.18, 8.51, 9.35, 7.91, 8.05, 8.95, 8.75, 11.22, 11.16, 10.26, 9.905, 8.99, 9.07, 9.78, 9.82, 9.18, 8.47, 8.15, 7.92, 7.81, 8.49, 8.15, 7.5, 8.33, 7.72, 9.39, 9.42, 9.1, 8.86, 8.62, 8.25, 8.32, 8.11, 8.57, 9.11, 9.3, 9.37, 9.22, 8.86, 8.87, 9.14, 10.63, 9.695, 9.785, 9.25, 10.31, 10.58, 11.55, 9.865, 11.64, 11.54, 11.85, 12.05, 11.92, 10.96, 13.86, 14.02, 14.19, 14.16, 13.15, 12.11, 12.26, 12.04, 11.82, 11.3186]
    """
    # Try to automatically detect decimal separator
    list_prices = extract_column_from_csv(csv_path=csv_path, column=column,days=days, round=round)
    print(list_prices)
    return list_prices

@mcp.tool()
def calculate_returns_mcp(prices:list[float]):
    """
    Calculate simple returns from a sequence of p
    return calculate_var_cvar_historical(returns=returns, significance_level=significance_level)rices.

    Parameters:
    prices: array-like, sequence of prices

    Returns:
    list: returns as a list of floats

    input example:
    {
    "prices": [21.14,21.15,21.15,21.16,21.18,21.17,21.18,21.16,21.09,21.13,21.13,21.15,21.13,21.02,21.02,21.01,21.03,21.04,21.03,21.04,21.05,21.08,21.07,21.1,21.11,21.14,21.15,21.15,21.16,21.16,21.16,21.17,21.04,21.02,21.0,20.96,20.98,20.99,20.97,21.0,20.98,20.89,20.69,20.87,20.87,20.97,20.96,20.97,20.98,20.98,21.03,21.05,20.89,20.89,20.91,20.89,20.93,20.94,20.95,21.01,21.04,21.07,21.02,21.01,21.03]
    }
    """
    return calculate_returns(prices=prices)

# Add an addition tool
@mcp.tool()
def calculate_var_cvar_historical_mcp(returns:list[float], significance_level:float=0.05):
    """
    Calculate historical VaR and CVaR for a given returns series or array.

    Parameters:
    returns: array-like, series of returns
    significance_level: float, confidence level (0.05 for 95% VaR/CVaR)

    Returns:
    dict: VaR and CVaR calculations

    input example:
    { 
        "returns": [1.14,2.1,2.5,2.1,..], 
        "significance_level": 0.05
    }
    """
    return calculate_var_cvar_historical(returns=returns, significance_level=significance_level)

@mcp.resource("yfinance-data://{ticker}/{period}/{save_file}/{column_name}")
def download_yfinance_data(ticker: str, period: str = '2y', column_name: str="Close", save_file:bool = False) -> dict:
    """
    Download historical data from Yahoo Finance for a given ticker and period.

    Parameters:
    ticker: str, stock ticker symbol
    period: str, data period ('1y', '2y', '5y', etc.)

    Returns:
    dict: Historical price data as a dictionary
    """
    try:
        print(f"Parameters: ticker={ticker}, period={period}, column_name={column_name}, save_file={save_file}")
        stock = yf.Ticker(ticker)
        data = stock.history(period=period)
        # print('Downloading ... ',data.shape,' |')
        if data.empty:
            raise ValueError(f"No data found for ticker {ticker} and period {period}")
        
        if save_file:
            date_str = datetime.now().strftime("%Y%m%d_%H%M%S")
            file_name = f'datasource/{ticker}_{date_str}.csv'
            data.to_csv(file_name)
            return {"file_name": file_name}
        else:
            return data.reset_index().to_dict(orient='list')[column_name]
    except Exception as ex:
        print(f'There is an error-------------------, \n{ex}')

def main():
    """Main function to run the MCP server"""
    mcp.settings.sse_path = '/mcp-market-risk'
    mcp.settings.port = 8000
    mcp.run(transport='sse')

if __name__ == "__main__":
    main()
