# Project
A parallel quick sort algorithm based on [oneTBB](https://github.com/oneapi-src/oneTBB).
In the benchmark the implementation is compared against its sequential version (`seq`), and STL version (`std`). The comparison is performed on four integer datasets of size $10^8$. The integers are generated randomly and are in range [0, `max_value`] where the `max_value` is iteratively chosen from $\{ 10^2, 10^4, 10^6, 10^8 \}$. For each of these values the experiments are performed five times with different seeds and then the mean value is calculated. To exclude the dataset creation overhead, a dry run (`io_bench`) is performed and then its running time is subtracted from the other algoritms' results.  

# Results
| `max_value`  | Parallel version speedup |
|--------------|--------------------------|
| 100          | 1.813802                 |
| 10000        | 2.550652                 |
| 1000000      | 3.334386                 |
| 100000000    | 4.248396                 |

<details>
    <summary>Detailed results</summary>

```
                  1    2    3    4    5   Mean        Std
Io_bench                                                        
data_100        693  622  625  662  638  648.0  29.690066
data_10000      654  624  716  712  632  667.6  43.781275
data_1000000    719  683  647  737  732  703.6  38.036824
data_100000000  644  641  647  677  628  647.4  18.063776
                   1     2     3     4     5    Mean        Std  AlgoTime
Par                                                                        
data_100        1742  1555  1629  1570  1642  1627.6  73.968236     979.6
data_10000      2200  2109  2137  2149  2107  2140.4  37.878754    1472.8
data_1000000    2292  2427  2441  2467  2444  2414.2  69.804728    1710.6
data_100000000  2707  2652  2585  2702  2563  2641.8  65.982573    1994.4
                   1     2     3     4     5    Mean         Std  AlgoTime
Seq                                                                         
data_100        2411  2486  2339  2440  2448  2424.8   54.924494    1776.8
data_10000      4527  4409  4373  4435  4377  4424.2   62.778977    3756.6
data_1000000    6327  6326  6478  6446  6460  6407.4   74.718137    5703.8
data_100000000  9223  9126  9167  9145  8941  9120.4  106.676145    8473.0
                    1      2      3      4      5     Mean        Std  AlgoTime
Std                                                                              
data_100         9431   9444   9479   9546   9514   9482.8  47.882147    8834.8
data_10000      11012  10850  10873  10893  10821  10889.8  73.387329   10222.2
data_1000000    12353  12406  12262  12314  12234  12313.8  69.081112   11610.2
data_100000000  13286  13252  13266  13184  13211  13239.8  41.571625   12592.4
```

</details>

# Usage 
- `./run_experiments.sh` -- Run experiments & produce results.
- `./run_tests.sh` -- Run algorithm correctness testing.

Python 3.6+ with installed `pandas` library is required for the report processing.

# Experiments environment
- GCC version: g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0.
- OS: Ubuntu 22.04 LTS, Windows Subsystem for Linux (WSL 2).
- Processor: AMD Ryzen 9 5900HS, cores: (4 physical, 8 virtual)