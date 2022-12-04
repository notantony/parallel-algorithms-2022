# Project
A parallel quick sort algorithm based on [oneTBB](https://github.com/oneapi-src/oneTBB).
In the benchmark the implementation is compared against its sequential version (`seq`), and STL version (`std`). The comparison is performed on four integer datasets of size $10^8$. The integers are generated randomly and are in range [0, `max_value`] where the `max_value` is iteratively chosen from $\{ 10^2, 10^4, 10^6, 10^8 \}$. For each of these values the experiments are performed five times with different seeds and then the mean value is calculated. To exclude the dataset creation overhead, a dry run (`io_bench`) is performed and then its running time is subtracted from the other algoritms' results.  

# Results
| `max_value`  | Parallel version speedup |
|--------------|--------------------------|
| 100          | 1.757855                 |
| 10000        | 2.753505                 |
| 1000000      | 3.987637                 |
| 100000000    | 5.279658                 |

<details>
    <summary>Detailed results</summary>

```
                  1    2    3    4    5   Mean         Std
Io_bench                                                         
data_100        698  670  653  637  700  671.6   27.609781
data_10000      680  729  699  673  760  708.2   36.175959
data_1000000    749  713  658  940  782  768.4  106.378099
data_100000000  700  752  796  694  694  727.2   45.532406
                   1     2     3     4     5    Mean         Std  RealTime
Par                                                                         
data_100        1935  1777  1668  1874  1737  1798.2  106.778743    1126.6
data_10000      2129  2250  2258  2302  2448  2277.4  114.955644    1569.2
data_1000000    2730  2409  2348  2345  2341  2434.6  167.485223    1666.2
data_100000000  2806  3021  2626  2634  2715  2760.4  162.859756    2033.2
                    1      2      3      4      5     Mean         Std  RealTime
Seq                                                                               
data_100         2613   2847   2671   2591   2538   2652.0  118.978990    1980.4
data_10000       5341   4841   4878   4962   5123   5029.0  205.434905    4320.8
data_1000000     7094   7146   7122   7386   8315   7412.6  517.702424    6644.2
data_100000000  11408  11507  11495  11473  11426  11461.8   43.147422   10734.6
                    1      2      3      4      5     Mean         Std  RealTime
Std                                                                               
data_100        11503  11580  11484  11749  11436  11550.4  122.536933   10878.8
data_10000      13122  13222  13276  14172  13259  13410.2  430.025813   12702.0
data_1000000    14919  14931  14997  14965  14211  14804.6  333.230851   14036.2
data_100000000  14160  13675  13961  13781  13978  13911.0  188.139576   13183.8
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