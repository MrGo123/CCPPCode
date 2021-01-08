#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;
int main()
{
    // 输入字符串
    string s;
    getline(cin, s);
    // cout << "you enterred:" << s << endl;

    string::iterator iter = s.begin();

    //去除首空格 
    while (iter != s.end())
    {
        if (*iter != ' ')
            break;
        s.erase(iter);
    }    

    // 去除尾空格
    int j=s.size()-1;
    while (s[j] == ' ')
    {
        s.erase(s.begin()+j);
        j--;
    }

//  cout << "string deletespace:" << s << endl;
    // 字符串整体翻转
    reverse(s.begin(), s.end());
    // cout << "string reversed:" << s << endl;
    // 单词翻转
    for (int i = 0, wordEnd = 0; i < s.size() + 1; i++)
    {

        if (s[i] == ' ' || s[i] == '\0')
        {
            reverse(s.begin() + wordEnd, s.begin() + i);
            wordEnd = i + 1;
        }
    }
    cout<<endl;
    cout << s;

    system("pause");
    return 0;
}
/*
"    up! day day study, good good"
"good good study, day day up!"
"the sky is blue after you outputted this  "
"this outputted you after blue is sky the"
*/

/*
The consensus among many Vim/Emacs users creates a picture many tech users from a certain generation would be familiar with. As my father would attest, using his Microsoft Zune long after its support ran out, if it ain't broke While there are many IDEs on the market, there's no reason to use one if you don't have to use one. It's the same reason I am still using Notepad to compose and not some fancy text editor or CMS tool. It just works."The reason I avoided IDEs to begin with was that back when I was getting into Vim, like a decade ago, it was an extra license to look into," says Vim user John Carter (not of Mars). "Since then it’s become a question of 'code speed.' If I start with a new IDE or even switch to something like Emacs, I’ll slow down. On an emotional and professional level, I can’t really afford that. It takes energy to pivot to a new editor. I don’t have that energy. I got the job, a family, and side projects. It seems silly but that kind of pivot takes energy."Vim is always available. Any Linux machine has it. Vim has a small footprint, low latency, fast startup, allows for more screen space, customizable and most importantly, once the muscle-memory has been ingrained, it’s nearly impossible to switch to something else.Continues Carter: "Our fingers are often the bottleneck between thinking up code and getting it in the app, so that’s where folks look to optimize shortcuts."Take Atom, one of the more popular IDEs/editors. Atom is a free, open-source text editor that bills itself as being "hackable to the core," allowing for multiple customizations. It has cross-platform editing, four UIs, eight syntax themes and integrates with HTML, Javascript, CSS, and Node.js. Most importantly for users who didn’t start coding in the last five years, there is a Vim Mode package. This has led users to literally turn Atom into Vim, unable to let go of the past, unwilling to fully embrace the future of code editing.
*/