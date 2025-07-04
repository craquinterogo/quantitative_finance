# Quantitative Finance MCP Server

A Model Context Protocol (MCP) server is created for testing how it works for instance to calculate Historical Value at Risk given a CSV with historical prices of stock RGTI.

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
Being in the folder `LLM/mcp-server`, run following commands.

Install required dependencies for MCP-server.
```bash
pip install -r requirements.txt
```

Install the mini-library created for VaR calculations `my-var` execute the command below.
```bash
pip install -e .
```

## Usage

### Running the Server
```bash
python server.py
```

## Configuration

A `mcp.json` file requires to be created to work as workspace server, with the content as shown below. More details about connection from Github Copilot in Agent mode [here](https://code.visualstudio.com/docs/copilot/chat/mcp-servers).

```json
{
    "servers": {
        "quant-mcp-server": {
            "type": "sse",
            "url": "http://127.0.0.1:8000/sse"
        }
    }
}
```
# Testing MCP server with Github copilot

Promt for testing quant-mcp-server is 

> Identify the absolute path of the CSV in this workspace and then use quant-mcp-server to retrieve the last 253 days of the "close" column. Use these values to calculate the returns, and subsequently calculate VaR and CVaR. Take into account the expected input format. No additional script is required. Be flexible with the number of decimals so that you don't modify outputs. Do not apply any rounding or truncation.

More details in 

# License

MIT License