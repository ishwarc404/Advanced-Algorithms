#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 63 /* {$,0-9,A-Z,a-z}*/
int findRange(char c)
{
	int ret =0;
	if(c>='a'&& c<='z')
		ret = 36 + (c-'a');
	else if(c>='A' && c<='Z')
		ret = 11 + (c-'A');
	else
		ret = 1+(c-'0');
	ret++;
	return ret;
}
int * SortDouble(char * string, int l,  int *order,  int * clas)
{
	int len = strlen(string);
	int *newOrder = (int*)malloc(sizeof(int)*len);
	int *count = (int*)malloc(sizeof(int)*len);
	memset(count, 0, sizeof(int)*len);

	for (int i=0; i<= len -1; i++)
		count[clas[i]]++;

	for (int i=1; i<= len -1; i++)
		count[i] += count[i-1];

	for (int i= len -1; i>=0; i--)
	{
		int before = (order[i]-l+len)%len;
		//Get class index for this
		int c = clas[before];
		count [c] = count[c] -1;//Decrement that count;
		newOrder[count[c]] = before;
	}
	return newOrder;
}
int * ComputeClass( int *order,  int *clas, int l, int str_len)
{
	int * newClass = (int *)malloc(str_len *sizeof(int));
	newClass[order[0]] = 0;
	for (int i =1; i<=str_len-1;i++)
	{
		// Compare first half
		if(clas[order[i]]!= clas[order[i-1]])
			newClass[order[i]] = newClass[order[i-1]] + 1;
		else
		{
			// Comapre second half
			if(clas[(order[i]+l)%str_len]  !=  clas[(order[i-1]+l)%str_len])
				newClass[order[i]] = newClass[order[i-1]] + 1;
			else
				newClass[order[i]] = newClass[order[i-1]] ;
		}
	}
	return newClass;
}
void computeLCP(const char * string, int *order, int size)
{
    int rank[size], lcp[size] ;
    /*
     * Iterate Suffix array and store the rank for each suffix from that index
     * for example string
     * 0 1 2 3 4 5
     * b a n a n a
     * 5 3 1 0 4 2  -> Suffix Array
     * At index 0 of string suffix is banana  Rank= 3
     * At index 1 of string suffix is anana   Rank= 2
     * At index 2 of string suffix is nana    Rank= 5
     * At index 3 of string suffix is ana     Rank= 1
     * At index 4 of string suffix is na      Rank= 4
     * At index 5 of string suffix is a       Rank= 0
     *
     * So just iterate 0 to len -1 and Rank[Suffix[i]] = i
     */
    for(int i=0; i<size; i++)
        rank[order[i]] = i;

    int lastLCP = 0;
    for(int i=0; i<size; i++)
    {

        if(rank[i]==size-1)
        {
            //Last lexiographic suffix , its LCP will always be 0
            lcp[rank[i]] = 0;
            continue;
        }
        /*
         * Start with suffix at this index , find what will be the next suffix after it (in lex order)
         * For this rank[i]+1 and index in SA , you will get string index where next suffix begin.
         * Start matching AFTER lastLCP
         *
         */
        int currentSuffix = i;
        int nextSuffix = order[rank[i]+1];

        int matchIndex = lastLCP;
        while((currentSuffix+matchIndex < size-1) && (nextSuffix+matchIndex < size-1) && (string[currentSuffix+matchIndex]==string[nextSuffix+matchIndex]))
        {
            matchIndex++;
            lastLCP++;
        }
        lcp[rank[i]] = lastLCP;
        if(lastLCP>0)
            lastLCP--;
    }
    for (int i=0; i<size; i++) //
            printf("%d ", lcp[i]);  //Prints LCP

}
int main(int argc, char *argv[])
{
	if(argc !=2)
	{
		printf ("usage: ./suffix_array string\n");
		return 0;
	}
	int len = strlen(argv[1]);
	len++;// For '$'
	//Append special character `$` at the end of string
	char * string = (char *) malloc(len+1);
	sprintf(string,"%s$",argv[1]);
	//printf("Modified = %s\n", string);
	// Initialization phase:
	// First count number of occurence of each different literals.
	int count [MAX_SIZE] = {0};
	for (int i=0; i<len; i++)
		if(string[i]=='$')
			count [0] = 1;// `$
		else
			count [findRange(string[i]) ] ++;
	/* Now compute the sum
	 We need to see where the next literals ends when array is sorted , for that we need to know where the previous one ends
	 For example for 'ababaa$' , sorted suffix of len=1 would be $aaaabb
	 Counting sort gives
	 $ = 1
	 a = 4
	 b = 2
	 Now 'a' will ends at 5 because `$` ends at 1 + occurence of a count 2 = 4, similar b ends at 7 because a ends at 5 + occurence of b count 2 = 7
	 1 2 3 4 5 6 7
	 $ a a a a b b ->sorted
	 counting sort array after adding previou
	 $ = 1
	 a = 5
	 b = 7
	*/
	for (int i=1; i<MAX_SIZE; i++)
		count [i] += count [i-1];
	 int * order = ( int *) malloc(sizeof( int) * len);
	/* len = 7
	 * 0 1 2 3 4 5 6
	   a b a b a a $ -> unsorted
        j s c             0 1 2 3 4 5 6
	   |6|$|0|   order = [6, , , , , , ]
	   |5|a|4|   order = [6, , , ,5, , ]
	   |4|a|3|   order = [6, , ,4,5, , ]
	   |3|b|6|   order = [6, , ,4,5, ,3]
	   |2|a|2|   order = [6, ,2,4,5, ,3]
	   |1|b|5|   order = [6, ,2,4,5,5,3]
	   |0|a|1|   order = [6,0,2,4,5,1,3]
	 */
	for (int j = len -1; j>=0; j--)
	{
		int c = string[j]=='$'?--count[0]:--count[findRange(string[j])];
		order [c] = j;
	}
	// Order contains [6, 0, 2, 4, 5, 1, 3] Index of suffix start of length 1 in sorted order

	// Compute clas , this is basically different type of literals that exists for ababaa$ , suffx len 1 , literals are $, a, b
	 int * clas = ( int *) malloc(sizeof( int) * len);
	/*
	 *  j o s p             0 1 2 3 4 5 6                 j = loop, o = order[j], s = string[order[j]], p=previous string
	   |1|0|a|$|   clas	 = [1, , , , , ,0]
	   |2|2|a|a|   clas  = [1, ,1, , , ,0]
	   |3|4|a|a|   clas  = [1, ,1, ,1, ,0]
	   |4|5|a|a|   clas  = [1, ,1, ,1,1,0]
	   |5|1|b|a|   clas  = [1,2,1, ,1,1,0]
	   |6|3|b|b|   clas  = [1,2,1,2,1,1,0]
	 *
	 */
	clas[order[0]] = 0;
	for (int i=1; i<len; i++)
		if(string[order[i-1]]!= string[order[i]])
			clas[order[i]] = clas[order[i-1]]+ 1;
		else
			clas[order[i]] = clas[order[i-1]];

	// Generalistion Phase , here we sort suffix of double length until < |S|
	int l = 1;
	while(l < len)
	{
		int *newOrder = SortDouble(string, l, order, clas);
		int *newClass = ComputeClass(newOrder, clas, l, strlen(string));
		//Free Older order & class memory
		free(order);
		free(clas);
		order = newOrder;
		clas = newClass;
		l = 2*l;
	}
	computeLCP(string, order, len);
	printf("\n");
	// newOrder is what is final output contains index of all suffix of a given string
	for (int i=0; i<len; i++) // start with i=1 to skip $
		printf("%d ", order[i]);  //Prints Suffix index in string in lexographical order
		//printf("%.*s\n", len-order[i]+1, (string+order[i])); //To print $ as well , start i as 0
		//printf("%.*s\n", len-order[i]+1, (argv[1]+order[i])); // Prints suffix in lexographical order

}