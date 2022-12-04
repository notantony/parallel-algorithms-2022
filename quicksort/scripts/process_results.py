import os
import pandas as pd


io_data = pd.read_csv('./results/io_bench.csv', sep=' ', index_col=0, header=None)
par_data = pd.read_csv('./results/par.csv', sep=' ', index_col=0, header=None)
seq_data = pd.read_csv('./results/seq.csv', sep=' ', index_col=0, header=None)
std_data = pd.read_csv('./results/std.csv', sep=' ', index_col=0, header=None)

io_mean = io_data.mean(axis=1)

print('Results:')
print((seq_data.mean(axis=1) - io_mean) / (par_data.mean(axis=1) - io_mean))
print('==================')
print('IO_mean:')
print(io_mean)

print('Par:')
print(par_data.mean(axis=1) - io_mean)
print('Seq:')
print(seq_data.mean(axis=1) - io_mean)
print('Std:')
print(std_data.mean(axis=1) - io_mean)


if detailed := False:
    for x in [io_data, par_data, seq_data, std_data]:
        mean = x.mean(axis=1)
        std = x.std(axis=1)
        x['Mean'] = mean
        x['Std'] = std
        if x is not io_data:
            x['AlgoTime'] = mean - io_mean
        print(x)