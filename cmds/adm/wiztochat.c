// tochat.c 
// Modify by Jingxue for XYCQ 6.23.2003

#include <ansi.h>
inherit F_CLEAN_UP;

int check_legal_title(string);
 
int main(object me, string arg)
{
	int n = 0;
	if( !arg ){
    		if(strlen(me->query("chaninfor/tochat"))>1)
    		{
    			printf("你目前的频道名称是：%s\n",(string)me->query("chaninfor/tochat"));
	    		if((int)me->query("chaninfor/tochat_time")>1)
    				printf("\n你已经设置过%s次频道名称。\n",chinese_number((int)me->query("chaninfor/tochat_time")));
		}
		else
		  	printf("你目前没有任何自设的频道名称。\n");
    		return 1;
	}

	if((int)me->query("daoxing") < 5000000)
	{
    		printf("你目前的道行不足五千年，无法设置自设频道名称。\n");
    		return 1;
	}
	if((int)me->query("chaninfor/tochat_time")>1 )
	{
		n = (int)me->query("chaninfor/tochat_time");
		if ((int)me->query("daoxing")/5000000 < n+1)
		printf("\n你已经设置过%s次频道名称，你的道行修为不足够再设置一次。\n",chinese_number((int)me->query("chaninfor/tochat_time")));
	}
	if(check_legal_title(arg) == 0) return 1;	
	
	me->set("chaninfor/tochat", trans_color(arg));
	me->add("chaninfor/tochat_time", 1);

	printf("你成功地将自己的自设频道名称部份设定为：%s\n",(string)me->query("chaninfor/tochat"));

    	return 1;
}
 
int check_legal_title(string addtitle)
{
       	int i;
       	string str;

	str = filter_color(trans_color(addtitle));
	i = strlen(str);

	write("。"+str+"。\n");
	if(strlen(addtitle) > 20){
    		printf("对不起，你的自设频道名称太长了。\n");
    		return 0;
	}

	if(strlen(str) !=4){
    		printf("对不起，你只能设置四个中文字作为自设频道名称。\n");
    		return 0;
	}

	while(i--) {
               	if( str[i]<=' ') {
                       	write("对不起，你的自设频道名称不能用控制字元。\n");
                       	return 0;
               	}
               	if( !is_chinese(str) ) {
                       	write("对不起，请您用「中文」设频道名称。\n");
                       	return 0;
               	}
       	}

	return 1;
}

int help(object me)
{
    write(@HELP
指令格式: tochat ***
 
自己设定自设频道名称。道行超过5000年可以设置四个中文的频道名称。
每5000年能设置一次。

请注意设置名称的恰当性，否则将取消此玩家设置的权利。

tochat 显示你目前的自设频道名称。

HELP
    );
	return 1;
}
 
