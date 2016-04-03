第一部分:
		
宣告一個指標陣列*array[12]來儲存資料，先將他每一格的第一格設為0(之後用來辨識有沒有資料已經在這一格內了），然後用fgets的方式讀輸入的字串，搭配while讓他能一直讀
	
	
將讀進來的字串去掉\n，變成\0(因為fgets會在字串結尾加\n)
		

先判斷字串是不是"exit"，如果是就break掉回到主選單
		
呼叫第一部分的hashfunction，傳入讀進來的字串到function內，回傳hashnumber
		
用while去不斷的判斷array[hashnum]內是否已有資料(!=0)，有的話就將hashnum++
		
malloc一個記憶體把字串複製到array[hashnum]內，作儲存的動作
		
		

→第一部分的hashfunction：
				
	傳入一個字串，用for迴圈去跑每個字母，把每個字母的ascii碼加起來，return mod12的數值



第二部分：
		
宣告一個指標陣列*array[HASHSIZE](HASHSIZE = 5000)，也是先將每一格的第一格設為0
		
宣告一個檔案指標fp，用scanf讀取檔案名稱，再用fopen開啟檔案
	
	
用while搭配fgets的方式不斷的讀入資料直到沒有資料為止，把每一個讀進來的字串結尾都變成\0
		
一樣先判斷讀進來的字串是不是"exit"，是的話就break
	
	
呼叫第二部分的hashfunction，傳入讀進來的字串到function內，回傳hashnumber

		
一樣while去不斷的判斷array_2[hashnum]內是否已有資料(!=0)，有的話就將hashnum++，collision也++
		
一樣malloc作儲存的動作，每成功儲存一筆data_num就++

		

→第二部分的hashfunction：
				
傳入字串型態，將hashvalue初始值設為0，用一個for迴圈去跑每個字，hashvalue往左shift 5bits後加上第一個字的值，再往左shift 5bits後加上第二個字的值，以此類推，會得到一個hashvalue，return mod HASHSIZE的數值
		


				
