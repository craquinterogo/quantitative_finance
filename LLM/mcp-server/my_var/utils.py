import pandas as pd

def extract_column_from_csv(csv_path: str, column: str, days: int, round:int=4) -> list[float]:
    """
    Extract the last N values from a specified column in a CSV file containing historical prices.

    Parameters:
    csv_path: str, absolute path to the CSV file
    column: str, column name to extract values from
    days: int, number of last days to extract

    Returns:
    list: last N values from the specified column
    """
    # Try to automatically detect decimal separator
    df = pd.read_csv(csv_path, sep=',', decimal='.')
    if column not in df.columns:
        raise ValueError(f"Column '{column}' not found in CSV file.")
    values = df[column].dropna().round(round).values
    if len(values) < days:
        raise ValueError(f"CSV contains only {len(values)} rows, but {days} requested.")
    return values[-days:].tolist()