// ask.c
#include <ansi.h>
inherit F_CLEAN_UP;

varargs string query_inquiry(object ob,int raw);

string *msg_dunno = ({
        "摇摇头，说道：这个...这个,我没听说过。\n",
        "睁大眼睛望着你，显然不知道你在说什么。\n",
        "耸了耸肩，很抱歉地说：无可奉告。\n",
        "说道：嗯....这我可不清楚，你最好问问别人吧。\n",
        "想了一会儿，说道：对不起，你问的事我实在没有印象。\n"
});

int main(object me, string arg)
{
        string dest, topic, msg;
        object ob;

        seteuid(getuid());

        if( !arg || sscanf(arg, "%s about %s", dest, topic)!=2 )
                return notify_fail("你要问谁什么事？\n");

        if( !objectp(ob = present(dest, environment(me))) )
                return notify_fail("你看清楚点:这里没有这个人耶。\n");
	if( me==ob )
		return notify_fail("你陷入了人格分裂，在自言自语。\n");
        if( !ob->is_character() || ob->is_no_look() ) 
        	return notify_fail("你对着"+ob->name()+"自言自语....\n");
        if( !ob->query("can_speak") ) 
        	return notify_fail("你向"+ob->name()+"打听有关『" + topic + "』的消息，但是它显然听不懂人话。\n");
        if( !living(ob) ) 
        	return notify_fail("但是很显然的，"+ob->name()+"现在的状况没有办法给你任何答覆。\n");
        if ( ob->is_fighting() ) 
        	return notify_fail("有什么事打完架再说！\n");
        
//预设主题的回答,其中有一个 "all"相当的不错,玩家解迷的时候方便多多....呵呵
	if( !INQUIRY_D->parse_inquiry(me, ob, topic) )
        	write("你向"+ob->name()+"打听有关『" + topic + "』的消息。\n");
	if( msg = ("/std/quest.c")->quest_ask (me, ob, topic) ) 
	{
        	if( stringp(msg) ) 
                {
                	write(CYN+ob->name()+CYN"说道：" + msg + "\n" NOR);
                        return 1;
		}
	}           	
	if( userp(ob) )
		return 1;
	if( msg = ob->query("inquiry/" + topic) ) 
	{
        	if( stringp(msg) ) 
                	write(CYN+ob->name()+CYN"说道：" + msg + CYN"\n" NOR);
                return 1;
	}
	if( topic=="噩梦"
	 && ob->query("family/family_name")==me->query("family/family_name")
	 && ob->query("inquiry/kill")
	 && !ob->query("inquiry/噩梦") )
	{
		msg = ("/quest/family/mieyao.c")->change_level(me);
		if( msg && stringp(msg) )
                	write(CYN+ob->name()+CYN"说道：" + msg + CYN"\n" NOR);
                return 1;
	}
	if(topic=="name")
	{
        	write(CYN+ob->name()+CYN"说道：我的名字就是"+ob->name()+CYN"，" + RANK_D->query_respect(me)+ "有什么事？\n" NOR);
                return 1;
	}
        if(topic=="news")
        {
        	string str;
                str = NEWS_D->prompt_user(me);
                if( str )
                	write(CYN+ob->name()+CYN"对你点了点头，说道："+str);
                return 1;
	} 
        if(topic=="all")
        {
        	write(CYN+ob->name()+CYN"对你悄声说道:"+query_inquiry(ob,0)+"!\n" NOR);
                return 1;
	}
        if(topic=="here")
        {
        	msg = MISC_D->find_place(environment(me));
        	if( !msg || !stringp(msg) )
        		msg = environment(me)->query("short");
        	write(CYN+ob->name()+CYN"对你悄声说道:这里就是"HIW+msg+NOR CYN",你没听说过吗？\n" NOR);
                return 1;
	}
        write(CYN+ob->name()+CYN+msg_dunno[random(sizeof(msg_dunno))]+NOR);
        return 1;
        
}
//从npc身上读取inquiry
varargs string query_inquiry(object ob,int raw)
{
        int i=0;
        mapping inq;
        string str="", *indexs;
        
        if(mapp(inq=ob->query("inquiry")))
        {
        	indexs=keys(inq);
        	if( !indexs || !arrayp(indexs) || sizeof(indexs)<1 )
        		return "实在是对不起,我什么也不知道呀!";
        	if( raw )
        		return  "有关于 "HIB+indexs[random(sizeof(indexs))]+NOR CYN" 的事情,我很高兴告诉你!";
                for(i=0;i<sizeof(indexs);i++)
		{
                                str=indexs[i]+" "+str;
                }
                str="有关于 "HIB+str+NOR CYN"的事情,我很高兴告诉你!";
                return str;
	}
        return "实在是对不起,我什么也不知道呀!";
}

int help(object me)
{
   write( @HELP
指令格式: ask <someone> about <something>

这个指令在解谜时很重要, 通常必须藉由此一指令才能
获得进一步的资讯。
预设的询问主题:
        here
        name
        news
        all
HELP
   );
   return 1;
}

