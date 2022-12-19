import os
import pandas as pd


par_data = pd.read_csv('./results/par.csv', sep=' ', index_col=None, header=None)
seq_data = pd.read_csv('./results/seq.csv', sep=' ', index_col=None, header=None)

print('Results:')
print(f'Ratio: {float((seq_data.mean(axis=1)) / (par_data.mean(axis=1)).item())}')
print('==================')

if detailed := True:
    for x, name in [(par_data, 'par'), (seq_data, 'seq')]:
        mean = x.mean(axis=1)
        std = x.std(axis=1)
        x['Mean'] = mean
        x['Std'] = std
        print(f'{name}:')
        print(x)