先宣告一個結構，將係數和次方儲存起來

將polyA、polyB、polyC、polyD宣告為全域變數

用fopen的方式讀檔，fscanf的方式將資料儲存在變數內
每
次讀檔就呼叫insertIn函式，將資料串連起來成一個linked list

polyA和polyB串連好後，就呼叫polyadd函式，將兩個list結合儲存

最後呼叫polymul函式把A+B出來的polyC和polyB相乘

把全部的多項式用printList印出來



1.insertIn函式:
　　
因為隨機讀檔的關係，所以需要一個一個比較再將資料插入到對的位置，所以宣告兩個結構指標來跑互相比較的動作

head = NULL 為list empty的情況下
直接將head指向temp
temp->exp > head->exp 為新增的資料的次方大於頭的情況
則直接將temp接於head前
temp->exp < head->exp 
為新增的資料的次方小於頭的情況，則需要用到兩個指向結構的指標來做新增



2.polyadd函式:
　　
將用insertIn整理完的多項式A和B，相加起來，利用while來跑兩個list，如果A的第一筆資料的exp大於B，則直接把A串連到C，然後指向A的指標(poly1)往下位移一個，指向下一筆資料，繼續和B來做比對，如果小於B，則直接把B串連到C
如果A等於B，則coef相加，exp不變，最後檢查A和B有沒有多餘的項沒有被比對到，再把剩下的串到C


3.polymul函式:
　　
用雙層for來達到多項式乘法互乘的概念，然後呼叫insertIn把乘出來的資料一個一個串起來，成為一個新的list = polyD
