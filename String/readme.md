# 串

串是由0~n个字符组成的有限序列。串多应用于文本编辑中，具有较多的插入和删除操作。

# 基本操作

*   串初始化:根据给定的字符串常量初始化串
*   串销毁:释放串空间
*   串清空:置为空串，长度为0
*   插入:在源串的指定位置插入子串
*   删除:根据`start`和`end`来删除源串的部分
*   取子串:根据`start`和`end`从源串取并放到子串中
*   串连接：将串连接到源串后面
*   串拷贝:将一个串的值复制到另一个串
*   串比较：比较两个串是否相等
*   串匹配：在源串中找到子串的匹配下标
*   串替换:替换源串中的子串，可选择替换一个或所有

# 实现方式

## 数组实现

这里使用动态内存分配的数组来存储串。ADT声明类似于线性表，因为串是特殊的线性表。

    <span class="hljs-keyword">typedef</span> <span class="hljs-keyword">struct</span> {
        <span class="hljs-keyword">int</span> len;
        <span class="hljs-keyword">char</span> *str;
    } String;
    `</pre>

    ## 链表实现

    定义如下:

    <pre>`<span class="hljs-id">#denfine</span> <span class="hljs-tag">BLOCK</span> <span class="hljs-tag">16</span>

    <span class="hljs-comment">//链表节点</span>
    <span class="hljs-tag">typedef</span> <span class="hljs-tag">struct</span> <span class="hljs-tag">Node</span> {
        <span class="hljs-attribute">char</span> str[BLOCK];
        <span class="hljs-attribute">String</span> *next;
    } <span class="hljs-attribute">Node</span>;

    <span class="hljs-comment">//串控制头，尾指针可以方便操作，如连接</span>
    <span class="hljs-tag">typedef</span> <span class="hljs-tag">struct</span> {
        <span class="hljs-attribute">Node</span> *head;
        <span class="hljs-attribute">Node</span> *tail;
        <span class="hljs-attribute">int</span> len;
    } <span class="hljs-attribute">String</span>;

链表实现的串定义不同于一般的单链表，而是采用效率更高的**块链串**形式。如果是普通的链表节点定义，若考虑**内存对齐**，则存储效率为50%，这样定义为75%。

若使用块链串形式，则当串的长度不为`Block`的倍数时，则需要填充上无效字符作为分界线。并且插入删除操作变得复杂，甚至在删除操作变多后，重整整个块里面的无效字符。