import pandas as pd

df = pd.read_csv('postal_data.txt') 	
csv_f = df.dropna()
csv_f_dropped_values = df[~df.index.isin(csv_f.index)]
csv_f.to_csv('postal_data.txt', encoding = 'utf-8', index = False)
csv_f_dropped_values.to_csv('faulty_postal_data.txt', encoding = 'utf-8', index = False)
