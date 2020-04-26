# Clex
Lexer based on C++ （基于C++的词法分析器）

# 1. Funtions
- （1）可以识别出用C语言编写的源程序中的每个单词符号，并以记号的形式输出每个单词符号。
- （2）可以识别并跳过源程序中的注释。
- （3）可以统计源程序中的语句行数、各类单词的个数、以及字符总数、并输出统计结果。
- （4）检查源程序中存在的词法错误，并报告错误所在的位置。
- （5）对源程序中出现的错误进行适当的恢复，使词法分析可以继续进行，对源程序进行一次扫描，即可检查并报告源程序中存在的所有词法错误。

# 2.State Transition Diagram

书本参考:

![书本参考](https://ae01.alicdn.com/kf/H3fa248c9dc1c4653a5d95f9764555cefA.png)

程序实现:

![程序实现](https://ae01.alicdn.com/kf/H7feec2bb501947e1a917e2f300a2fd6dp.png)

# 3.Test

## Test Example
```
int main(void){
	int a = 2;
	int b = 3;
	int c = a * b;
	float k = 3.14;
	float d = c + a / 3.14 * 2.4E+23;
	for (int i = 0; i < d; i++) {
	// test
	if (a == b) {
		if (a != b) {
		/*
			csdererwrew
		*/
		} else {
		}
	} else {
while(1);
	}
return 0;
}

"test string"
a.1
```

## Test Result
```
<int>
<Id,1>
<Op,(>
<void>
<Op,)>
<Op,{>
<int>
<Id,2>
<Op,=>
<Constant,2>
<Op,;>
<int>
<Id,3>
<Op,=>
<Constant,3>
<Op,;>
<int>
<Id,4>
<Op,=>
<Id,2>
<Op,*>
<Id,3>
<Op,;>
<float>
<Id,5>
<Op,=>
<Constant,3.14>
<Op,;>
<float>
<Id,6>
<Op,=>
<Id,4>
<Op,+>
<Id,2>
<Op,/>
<Constant,3.14>
<Op,*>
<Constant,2.4E+23>
<Op,;>
<if>
<Op,(>
<Id,2>
<Op,==>
<Id,3>
<Op,)>
<Op,{>
<if>
<Op,(>
<Id,2>
<Op,!=>
<Id,3>
<Op,)>
<Op,{>
<Op,}>
<else>
<Op,{>
<Op,}>
<Op,}>
<else>
<Op,{>
<while>
<Op,(>
<Constant,1>
<Op,)>
<Op,;>
<Op,}>
<return>
<Constant,0>
<Op,;>
<Op,}>
<StringLiteral,test string>
<Id,2>
Error at: 22line, 2 char.
lines:22
KeyWord:13 Op:36 Id:15 Constant:7 StringLiteral:1
words:256
```

# 4. Lisence

MIT Lisence

PS: 作为作业形式重写的基于C的小词法分析器。希望能给做实验的学弟or学妹一定参考。当然自己动手实现效果会更好。后期本程序在完善状态机的补充时应该没有写完，所以里面会有一些增加的特殊用例bug，请自行修复。

-Giria
