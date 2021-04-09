inherit SUPER_NPC;
#include <ansi.h>

string give_book();

void create_book()
{
	object book;
	remove_call_out("create_book");
	if( !environment() )
		return;
	book = present("lingfeng miji",this_object());
	if( !book || base_name(book)!="/d/baihuagu/obj/feng" )
		book = carry_object("/d/baihuagu/obj/feng");
	if( book )
		set_temp("my_book",book);
	remove_call_out("create_book");
	call_out("create_book",3600);
}

void create()
{
	set_name("黄月亮", ({"huang yueliang", "moon", "huang", "yueliang"}));
	set_level(120);
	set("long",@LONG
雪山孔雀王。
LONG);
	create_family("百花谷", 2, "弟子");
	set("title", HIY"孔雀王"NOR);
	set("gender", "男性");
	set("age", 135);
	set("attitude", "friendly");
	set("force_factor", 125);
	set("mana_factor", 100);
	set_skill("literate",1200);
	set_skill("unarmed", 1200);
	set_skill("dodge",1200);
	set_skill("force",1200);
	set_skill("parry", 1200);
	set_skill("sword", 1200);
	set_skill("zongheng-sword", 1200);
	set_skill("spells", 1200);
	set_skill("baihua-xianfa", 1200);
	set_skill("brightjade-force", 1200);
   	set_skill("siji-zhang",1200);
   	set_skill("rainbow-zhi",1200);
   	set_skill("wuyou-steps", 1200);
   	map_skill("unarmed", "siji-zhang");
   	map_skill("force", "brightjade-force");
   	map_skill("dodge", "wuyou-steps");
   	map_skill("sword", "zongheng-sword");
   	map_skill("parry", "zongheng-sword");
   	set_skill("jiefeng",1200);
   	set_skill("hutian",1200);
   	set("inquiry", ([
   		"寒玉灵风" : (: give_book :),
   		"book" : (: give_book :),
   	]));	
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"sword",1)->wield();	
	powerup(0,1);
	remove_call_out("create_book");
	call_out("create_book",5);
}

void attempt_apprentice(object ob)
{
        if( ob->query_level()<85 )
        {
        	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是打好基础再来吧。\n"NOR);
           	return ;
        }
        if( ob->query_level()>125)
        {
        	EMOTE_D->do_emote(this_object(), "wow",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是去找仙子吧。\n"NOR);
           	return ;
        }
        if( ob->query("class") && ob->query("class")!="xian" )
        {
        	if( !ob->query_temp("pendding/bhg_class") )
        	{
        		EMOTE_D->do_emote(this_object(), "wow",geteuid(ob),CYN,0,0,0);
        		tell_object(ob,CYN+name()+CYN"说道：以前并未见门内有"+RANK_D->query_respect(ob)+"，莫非你是散修出身？\n"NOR);
        		tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是先找百草仙询问「带艺拜师」了再说。\n"NOR);
           		return ;
           	}	
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们百花谷发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","百花谷又多了一个弟子  "+ob->name(1)+HIW"\n                                 百花谷的势力加强了。\n"NOR);
        return;
}

int prevent_learn(object who,string skill)
{
	if( skill!="zongheng-sword" )
                return 0;
	if( who && userp(who) && who->is_knowing("bhg_zongheng")>0 )
                return 0;
	tell_object(who,query("name")+"说道：你是从哪里得来的纵横剑法？\n");
	return 1;
}

int accept_object(object who,object obj)
{
	object book;
	string arg,*str,*temp;
	int i;
	if( !userp(who) )
		return 0;
	if( who->query("family/family_name")!="百花谷" )
		return 0;
	temp = who->query_temp("pedding/bhg_feng");
	if( !temp || !arrayp(temp) || sizeof(temp)<1 )
	{	
		str = who->query("mark/bhg_feng");
		if( !str || !arrayp(str) || sizeof(str)<1 )
			return 0;
		temp = str;	
		who->set_temp("pedding/bhg_feng",temp);	
	}
	if( member_array(obj->query("name"),temp)==-1 )
		return 0;
	book = query_temp("my_book");
	if( !book || !present(book,this_object()) )
	{
		EMOTE_D->do_emote(this_object(), "shake",geteuid(who),CYN,0,0,0);
		tell_object(who,CYN+name()+CYN"说道：书已经送给别人了。。。\n"NOR);
		return 0;
	}
	EMOTE_D->do_emote(this_object(), "hoho",geteuid(who),CYN,0,0,0);
	tell_object(who,CYN+name()+CYN"说道：好，有了这个，希望她也喜欢。。。\n"NOR);
	temp-= ({obj->query("name")});
	if( sizeof(temp)<1 )
	{
		if( book->move(who) )
			message_vision("$N递给$n一本"+book->name()+"。\n",this_object(),who);
		who->delete_temp("pedding/bhg_feng");
		who->delete("mark/bhg_feng");	
		return 1;	
	}
	who->set_temp("pedding/bhg_feng",temp);	
	arg = "";
	for(i=0;i<sizeof(temp);i++)
		arg+= temp[i]+CYN" ";
	tell_object(who,CYN+name()+CYN"说道：我还需要"+arg+"\n"NOR);
	return 1;
}

string give_book()
{
	int i;
	string arg,*str,*name1,*name2,name;
	object who = this_player();
	if( who->query("family/family_name")!="百花谷" )
		return 0;
	if( !query_temp("my_book") 
	 || !present(query_temp("my_book")) )
		return "书已经送给别人了。";	 	
	str = who->query("mark/bhg_feng");
	if( !str || !arrayp(str) || sizeof(str)<1 )
	{
		str = ({});
		arg = "";
		name1 = ({
			MAG "梦幻玫瑰" NOR,HIC "幻梦幽兰" NOR,HIB "薄雪花" NOR,HIG "风野玫" NOR,
			HIR "美人血" NOR,HIW "青凰玫" NOR,HIB "紫蔷薇" NOR, HIB "大丽花" NOR, 
			HIB "勿忘我" NOR,HIB "白玫瑰" NOR,HIB "翡翠绿" NOR,HIB "雪腊梅" NOR,
			HIB "曼陀罗" NOR,HIB "睡莲" NOR,
		});
		name2 = ({	
        		HIR"红玫瑰"NOR,HIW"白玫瑰"NOR,HIM"粉风信子"NOR, HIG"情人草"NOR,MAG"熏衣草"NOR,
        		HIC"蝴蝶兰"NOR,HIR"火百合"NOR,HIG"马蹄莲"NOR, HIW"满天星"NOR,HIM"粉金鱼草"NOR,
        		HIC"天堂鸟"NOR,HIB"勿忘我"NOR,HIY"黄康乃馨"NOR,HIM"紫丁香"NOR,MAG"紫郁金香"NOR,
		});
		name = name1[random(sizeof(name1))];
		str+= ({name});
		arg+= name;
		name = name2[random(sizeof(name2))];
		str+= ({name});
		arg+= CYN"和"NOR+name;
		who->set("mark/bhg_feng",str);
		return "你如果能将"+arg+CYN"给我，我自然可以给你。"NOR;
	}
	arg = "";
	for(i=0;i<sizeof(str);i++)
		arg+= str[i]+CYN" ";
	return "我需要"+arg+"，如果你能替我寻来，我自然给你秘籍。";
}	

int recruit_apprentice(object ob)
{
	 if( ::recruit_apprentice(ob) )
	 	ob->set("class","xian");
} 