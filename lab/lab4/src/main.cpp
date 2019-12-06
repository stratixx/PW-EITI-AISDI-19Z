#include <iostream>
#include <string>
#include <vector>
 
using namespace std;


unsigned long windowHash(const std::string& windowStr)
{
    unsigned long windowHash = 0;

    for( size_t n = 0; n<windowStr.size(); ++n)
    {
        windowHash = windowHash<<7; // 7 bitowe znaki
        windowHash += windowStr[n];
    }
    return windowHash;
}

unsigned long windowHashRecalc(const char outgoing, const char incoming, const size_t windowSize, unsigned long windowHash)
{
    windowHash -= outgoing << (7*(windowSize-1));
    windowHash = windowHash << 7;
    windowHash += incoming;

    return windowHash;
}

/*
    Testuję czy oszczędny hash daje te same wyniki co pełne wyliczanie hashu
*/
bool windowHashTest(const std::string& str, const size_t windowSize)
{
    unsigned long hash = 0;
    unsigned long hashRecalc = 0;

    hash = windowHash(str.substr(0, windowSize));
    hashRecalc = hash;

    for( size_t n=1; n<=str.size()-windowSize; ++n)
    {
        hash = windowHash(str.substr(n, windowSize));
        hashRecalc = windowHashRecalc(str[n-1], str[n+windowSize-1], windowSize, hashRecalc);
        if(hash!=hashRecalc)
        {
            cout<<"windowHashTest ERROR"<<endl;
            cout<<"pos="<<n<<" windowStr=\""<<str.substr(n, windowSize)<<"\""<<endl;
            cout<<"hash="<<hash<<" hashRecalc="<<hashRecalc<<endl;
            return false;
        }
    }
    return true;
}

/**
 * Source: https://eduinf.waw.pl/inf/alg/001_search/0052.php
    Finds occurences of given word in given string using the KR algorithm.
 
    @param  str   string to search (haystack)
    @param  key   word to find (needle)
    @return a vector of positions where the word begins
 
    @author Krystian Chachuła & Konrad Winnicki

    Example output:
    BABC
    CCABABABCBBBCAABCBCCAAAAACBABAABCABBBCCCCBCABACBBBBAABCBABCBACCACBBBABCBAAABBBA
         ^                                                 ^           ^
    5
    55
    67
*/
std::vector<int> findOccurrences(std::string& str, std::string& key)
{ 
    std::vector<int> occurrences;
    unsigned long hash, keyHash;
    size_t windowSize = key.size();
    size_t n=0;
    size_t stringCmp = 0;


    hash = windowHash(str.substr(0, windowSize));
    keyHash = windowHash(key);

    while(  n<=str.size()-windowSize)
    {
        if(hash==keyHash)
        {
            stringCmp++; // inkrementuj licznik porównań stringów
            if( str.substr(n, windowSize)==key )
                occurrences.push_back(n);
        }
        ++n;
        hash = windowHashRecalc(str[n-1], str[n+windowSize-1], windowSize, hash);
    };
    cout<<"stringCmp= "<<stringCmp<<"/"<<occurrences.size()<<endl;
    return occurrences;
}
 
int main(int argc, char * argv[])
{
    std::string S = "SFXTHKWCNMEWIEOCWBEIBEHHDBMCUNSPVCEUPQDOBSOUARRFOEGMDMJQRBMFISSVGCMJPUNUZPCPSNTKCZUZYTHWLZXBZWVAPMDAOXVWVUSFBJYZAUCSXGIFHHGQCJUNDKBYDXQGOCFGNHLNHEZZANGNERFMFOKTUYPCKOUJQRNQLTYEQJNDSSOVYFCXCOFTIRBPKENEMSFYSYRQQDVSDMGJWEEMHBOEHULKKYQPZDFQCNCLWDCXVHPTLJMAPVLEVJNBMXAABHZHUDMUQNSEGDEVGBDDASTNKRIJOWXSUVWVYWQJLGFJDZOVYWWGAXEZBOJDLPHOOHAOAUZQBMLKJJTCNXINXYLYPWJKQUWJHZQJWWYHIDJAFUVKKTKVHSVLIUTLXHUUSJGDWSWOJPGHUJOEYYFPFQNEWBPWZYSWVIUOMSCHSPLRWHRNLGGDMFTVQONEJBDLHGQJTOGNPHACCWJPJXXLBLETBUXDICDMJWSLJPKDMPUHJGMPBCTDEKKJQKWSNPIBKTZFSSYRVDSQGRFBNGYHQQGYWWBLFOBEOVPLFVIDGQSQSGZQUWFHILWBGRWVGMZOUJDIPUJIPUQSYGQYYAAUJCZQKTIARNRHHFOZYLCBMJNYCLPCNJULQGWBBRMSVUCIJQKYDYKMCKEONCSNPAJTTHHLOFYCFEKKYPOBUDGRSQOZVTJKDYXFZHEDXQAPQUEXLENMGJDBNCWDOGTVYAVYFTTONTPUZSYVQGWDUELUNAARDZOPNKWJLVHOUQKJTCILLBXZKWYGBYVKTBDHAHNEMVQLQVKSVUROYVGYBUKRXUCPDDGIIHPGAIRITGBFSPPDDHKXYMTQKMUWQRLVYTZUWCOKCROCDVCYWYPPPFMESVYHPSGJQWEOPUPJDLWPUTFGRBZIGNIENLFEWRBIRHQNELDMGOAUZFCQZQALLQRCBRELRERNUMUPQXPBKMRPZKPJHQOQPCKPROUPACHBEAIHRSQSDYUQWHOKSFXTHKWCNMEWIEOCWBEIBEHHDBMCUNSPVCEUPQDOBSOUARRFOEGMDMJQRBMFISSVGCMJPUNUZPCPSNTKCZUZYTHWLZXBZWVAPMDAOXVWVUSFBJYZAUCSXGIFHHGQCJUNDKBYDXQGOCFGNHLNHEZZANGNERFMFOKTUYPCKOUJQRNQLTYEQJNDSSOVYFCXCOFTIRBPKENEMSFYSYRQQDVSDMGJWEEMHBOEHULKKYQPZDFQCNCLWDCXVHPTLJMAPVLEVJNBMXAABHZHUDMUQNSEGDEVGBDDASTNKRIJOWXSUVWVYWQJLGFJDZOVYWWGAXEZBOJDLPHOOHAOAUZQBMLKJJTCNXINXYLYPWJKQUWJHZQJWWYHIDJAFUVKKTKVHSVLIUTLXHUUSJGDWSWOJPGHUJOEYYFPFQNEWBPWZYSWVIUOMSCHSPLRWHRNLGGDMFTVQONEJBDLHGQJTOGNPHACCWJPJXXLBLETBUXDICDMJWSLJPKDMPUHJGMPBCTDEKKJQKWSNPIBKTZFSSYRVDSQGRFBNGYHQQGYWWBLFOBEOVPLFVIDGQSQSGZQUWFHILWBGRWVGMZOUJDIPUJIPUQSYGQYYAAUJCZQKTIARNRHHFOZYLCBMJNYCLPCNJULQGWBBRMSVUCIJQKYDYKMCKEONCSNPAJTTHHLOFYCFEKKYPOBUDGRSQOZVTJKDYXFZHEDXQAPQUEXLENMGJDBNCWDOGTVYAVYFTTONTPUZSYVQGWDUELUNAARDZOPNKWJLVHOUQKJTCILLBXZKWYGBYVKTBDHAHNEMVQLQVKSVUROYVGYBUKRXUCPDDGIIHPGAIRITGBFSPPDDHKXYMTQKMUWQRLVYTZUWCOKCROCDVCYWYPPPFMESVYHPSGJQWEOPUPJDLWPUTFGRBZIGNIENLFEWRBIRHQNELDMGOAUZFCQZQALLQRCBRELRERNUMUPQXPBKMRPZKPJHQOQPCKPROUPACHBEAIHRSQSDYUQWHOK";
    std::string W = "SOUARRFOEGMDMJQRBMFISSVGCMJPUNUZPCP";
    std::vector<int> occurrences = findOccurrences(S, W);
 
    cout<< W<<endl;
    cout<< S<<endl;

    if( windowHashTest(S, W.size())==false)
        return -1;

    for (int i=0, k=0; i < S.size(); i++) {
        if(k>=occurrences.size())
            break;
        if(i==occurrences[k])
        {
            cout<<"^";
            k++;
        }
        else
            cout<<" ";
    }
    cout<<endl;

    for (int i=0; i < occurrences.size(); i++)
        cout << occurrences[i] << endl;

    return 0;
}