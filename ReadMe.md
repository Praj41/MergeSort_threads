# **Multi-threaded Implementation of Merge Sort and Quick Sort**

### Base Merge-Sort/Quick-Sort code taken form Geeksforgeeks

### Compare time between Merge Sort and Quick sort
#### Quick Sort provides some speedup compared to Merge Sort
#### CPU Intel core i7-9750H 6C/12T 4Ghz all core
#### 8 Threads spawned for sorting and arrays merged with merge tree
### As Tested with 40960k long int(s) in default release config:
**msvc**<br>
Quick sort ≃ 1 sec<br>
Merge sort ≃ 2.5 sec<br><br>
**clang++10 wsl 2 ubuntu**<br>
Quick sort ≃ 1 sec<br>
Merge sort ≃ 1.5 sec<br><br>