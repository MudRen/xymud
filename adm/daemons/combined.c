//combined.c
//炼化合成系统
//慢慢完善中...

#include <ansi.h>

string *lianhua = ({
        "/d/obj/drug/dieda",
        "/d/obj/drug/hunyuandan",
        "/d/obj/drug/jinchuang",
        "/d/obj/drug/dieda",
        "/d/obj/drug/hunyuandan",
        "/d/obj/drug/jinchuang",
        "/d/obj/drug/hunyuandan2",
        "/d/obj/drug/jinchuang2",
        "/d/obj/drug/hunyuandan2",
        "/d/obj/drug/jinchuang2",
        "/d/obj/drug/hunyuandan3",
        "/d/obj/drug/jinchuang3",
        "/d/obj/drug/hunyuandan3",
        "/d/obj/drug/jinchuang3",
        "/d/obj/drug/dx-lijing-2",
        "/d/obj/drug/dx-lijing-1",
        "/d/obj/drug/dx-rulai-kill-2",
        "/d/obj/drug/dx-rulai-kill-1",
        "/d/obj/drug/exp-lijing-1",
        "/d/obj/drug/exp-lijing-2",
        "/d/obj/drug/exp-rulai-kill-1",
        "/d/obj/drug/exp-rulai-kill-2",
        "/d/obj/drug/exp-rulai-kill-21",
        "/d/obj/drug/exp-rulai-kill-22",
        "/d/obj/fabao/bagua",
        "d/obj/fabao/xiang-hebao",
        "d/obj/fabao/taijitu",
        "/obj/weapon",
        "/obj/armor",
});

nosave mapping LIANHUA=([]);

void lianhua_end(object who,object npc,string file)
{
	int num = 1;    
	string unit;
	object ob;
	if( !npc )
        	return;
	if( !who || !present(npc,environment(who)) )
        {
        	map_delete(LIANHUA,who->query("id"));
        	return;
        }
	if( file!="失败" )
        {
        	ob = new(file);
        	if( ob->query_amount()>0 )
                	num = 10+random(100);
        	if( ob->query_time() )
                	num = 1;
        	if( num>1 )
                	ob->set_amount(num);
        	if( ob->query("unit") )
                {
                	if( ob->query("base_unit") )
                        	unit = ob->query("base_unit");
                	else    unit = ob->query("unit");
                }
        	else    unit = "个";                                    
        }
	if( !ob || !ob->move(who) )
        {
        	message_vision(CYN"$N"CYN"长嘘一口气，缓缓睁开双目，伸出双手，但见两掌之中空空如也！\n"NOR,npc,who);
        	npc->command("tell "+who->query("id")+" 甚是遗憾，你的妖精魄石炼化失败了。\n");
        }
	else    
	{
        	if ( num>0 )
                {
                message_vision(CYN"$N"CYN"长嘘一口气，缓缓睁开双目，伸出双手，但见两掌之中多出了"+chinese_number(num)+unit+ob->name()+CYN"！\n"NOR,npc,who);        
                CHANNEL_D->do_channel(npc,"chat","呵呵，好个造化，"+who->name()+"成功炼得"+chinese_number(num)+unit+ob->name()+HIC"。"NOR);
                }
        }
        map_delete(LIANHUA,who->query("id"));
        return;
}               

//who -- 需炼化者
//npc -- 提供炼化的对象
int do_lianhua(object who,object npc)
{
	string *ff,file;
	int i,k,x,time; 
	if( !who || !npc || undefinedp(LIANHUA[who->query("id")]) )
        	return 0;
	k = LIANHUA[who->query("id")];
	x = sizeof(lianhua);
	if( k>x )       
		k = x;
	ff = ({});
	i = 0;
	if( wizardp(who) && who->query("env/test") )
        {
        	i = 23;
        	k = x;
        }
	for(i;i<k;i++)
        	ff+= ({ lianhua[i] });
	if( random(k)==0 )
        	file = "失败";
	else    file = ff[random(sizeof(ff))];
//check
	npc->set("gift_arr",ff);
	message_vision(CYN"$N"CYN"朝$n"CYN"点了点头。\n"NOR,npc,who);
	message_vision(CYN"$N"CYN"说道：灵宝天尊，安慰身形。弟子魂魄，五脏玄冥。青龙白虎，队仗纷纭；朱雀玄武，侍卫我真。急急如律令。\n"NOR,npc,who);
	message_vision("\n言罢，$N闭目打坐，浑身顿时仙气缭绕，双手紧攥妖精魂石，运起无上仙法对之进行炼化。\n",npc,who); 
	npc->command("tell "+who->query("id")+" 贫道修炼期间千万别离开，有结果片刻便分明。");
	
	time = (1+k)*3;
	if( time>120 ) time = 120;
	if( wizardp(who) && who->query("env/test") )
       		time = 5;
	npc->start_call_out( (: call_other, __FILE__, "lianhua_end", who,npc,file :),time);
	return 1;
}      
