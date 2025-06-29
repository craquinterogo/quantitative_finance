import numpy as np
import pandas as pd

def calculate_returns(prices:list[float]):
    """
    Calculate simple returns from a sequence of prices.
    """
    print(f'We are in calculate_returns function, receiving {len(prices)} data points.')
    prices = np.asarray(prices).flatten()
    if len(prices) < 2:
        raise ValueError("At least two prices are required to calculate returns.")
    returns = (prices[1:] - prices[:-1]) / prices[:-1]
    return returns.tolist()

def calculate_var_cvar_historical(returns:list[float], significance_level:float=0.05):
    """
    Calculate historical VaR and CVaR for a given returns series or array.
    """
    try:
        if not isinstance(significance_level, float):
            significance_level = float(significance_level)
        # print("Step 1: Converting returns to numpy array and flattening.")
        returns = np.asarray(returns).flatten()
        # print(returns)
        # print(f"Step 2: Filtering NaNs. Input length: {len(returns)}")
        returns = returns[~np.isnan(returns)]
        # print(f"Step 3: After filtering NaNs. Length: {len(returns)}")
        if len(returns) == 0:
            raise ValueError("Returns array is empty.")

        # print("Step 4: Sorting returns ascending.")
        sorted_returns = np.sort(returns)
        n = len(sorted_returns)
        # print(f"Step 5: Number of sorted returns: {n}")
        var_index = int(np.floor(significance_level * n))
        var_index = max(0, min(var_index, n - 1))
        # print(f"Step 6: Calculated var_index: {var_index}")
        var_historical = sorted_returns[var_index]
        # print(f"Step 7: VaR (historical): {var_historical}")

        cvar_historical = sorted_returns[:var_index + 1].mean()
        # print(f"Step 8: CVaR (historical): {cvar_historical}")

        results = {
            'significance_level': (1 - significance_level) * 100,
            'n_points': n,
            'var_historical': var_historical,
            'cvar_historical': cvar_historical,
        }
        # print("Step 9: Returning results.")
        return results
    except Exception as e:
        print(f"Exception occurred: {e}")
        raise