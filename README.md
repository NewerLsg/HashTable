# HashTable
哈希表的实现
1.共享内存作为内存空间(共享内存key当前是随机)
2.使用拉链法解决冲突
3.节点空间[1024]和键空间大小[128]暂时固定
4.在src/nw_util.h中有多种哈希函数可以选择，现在只支持在初始化代码中静态指定。改成动态指定只需要修改初始化接口，传入相应的哈希函数即可

