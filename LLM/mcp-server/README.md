# Quantitative Finance MCP Server

A Model Context Protocol (MCP) server providing quantitative finance tools and calculations.

## Features

This MCP server provides the following tools and resources:

### Resources
- `yfinance-data://{ticker}/{period}` - Download historical stock data from Yahoo Finance
  - Parameters: `ticker` (stock symbol), `period` (1y, 2y, 5y, etc.)
  - Returns: Historical price data as dictionary with Date, Open, High, Low, Close, Volume

### Tools
- `calculate_returns(prices)` - Calculate simple returns from a sequence of prices
  - Input: Array of prices
  - Output: List of calculated returns
  
- `calculate_var_cvar_historical(returns, confidence_level=0.05)` - Calculate historical Value at Risk (VaR) and Conditional Value at Risk (CVaR)
  - Input: Array of returns, confidence level (default 0.05 for 95% confidence)
  - Output: Dictionary with VaR and CVaR calculations

## Virtual Environment Setup

As we'll work with many libraries that may create conflicts with existing environments, create a virtual environment:

```console
python3 -m venv quant-mcp-server
```

### Activating the Virtual Environment

Linux/macOS:
```console
source ./quant-mcp-server/bin/activate
```

Windows:
```console
./quant-mcp-server/Scripts/activate
```

## Installation

Install required dependencies:
```bash
pip install mcp fastmcp yfinance numpy pandas
```

Install in development/edit mode:
```bash
pip install -e .
```

## Usage

### Running the Server
```bash
python server.py
```

### Testing the Server
Use the provided client to test resources and tools:
```bash
python client.py
```

The client provides an interactive menu to:
1. List available resources
2. Test yfinance data retrieval
3. List available tools
4. Test VaR/CVaR calculations
5. Exit

### Example Usage

**Retrieving Stock Data:**
- Resource URI: `yfinance-data://AAPL/1y`
- Gets 1 year of Apple stock data

**Calculating Returns:**
```json
{
  "prices": [100, 101, 99, 102, 98]
}
```

**Calculating VaR/CVaR:**
```json
{
  "returns": [-0.02, -0.01, 0.01, 0.02, -0.03, 0.015, -0.005],
  "confidence_level": 0.05
}
```

## Development

Install development dependencies:
```bash
pip install -e ".[dev]"
```

Run tests:
```bash
pytest
```

Format code:
```bash
black .
isort .
```

Type checking:
```bash
mypy .
```

## Configuration

To use this MCP server with Claude Desktop or other MCP clients, add the following to your MCP configuration:

```json
{
  "mcpServers": {
    "quant-finance": {
      "command": "python",
      "args": ["/path/to/your/server.py"]
    }
  }
}
```

## Dependencies

- `mcp` - Model Context Protocol library
- `fastmcp` - Fast MCP server implementation
- `yfinance` - Yahoo Finance data retrieval
- `numpy` - Numerical computing
- `pandas` - Data manipulation and analysis
- `warnings` - Warning control

## License

MIT License

# Testing MCP server with Github copilot

Promt

I'd like to calculate the VaR using quant-mcp-server such that you use the column close and last 252 datapoints that correspond to the last 252 business days. Take into account the format of expected input as pointedout in expected input as example of description on each tool.



I'd like to calculate the VaR using quant-mcp-server such that you use the column close and last 252 datapoints that correspond to the last 252 business days. Take into account the format of expected input as pointedout in expected input as example of description on each tool. If possible do not create any python script in between, just execute it int terminal using the command option. Both returns and VaR calculator tools are available in MCP server. Ignore any previous calculation using pythonc command or script, focus only in MCP server.

I'd like to calculate the VaR using quant-mcp-server. The CSV file contains historical prices, but I want to calculate the VaR using the last 252 datapoints corresponding to last business date year. Furthermore, I want you use the MCP tools #calculate_returns and #calculate_var_cvar_historical  for this task. No any other thing is required