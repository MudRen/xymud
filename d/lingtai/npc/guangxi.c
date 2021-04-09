// guang.c
#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

int borrow_me(object ob);
int borr_me(object ob);
string yinyang_shu();

void create()
{
        set_name("广羲子", ({"guang xizi", "guang"}));
        set_level(110);
        set("title", "经阁总管");
        set("gender", "男性" );
        set("age", 53);
        set("long", "一个看起来慈眉善目的道士，正拿着一本经书读着．\n");
	set("class", "toaist");
        set("attitude", "friendly");
	set("force_factor", 40);
	set("mana_factor", 30);
        set("eff_dx", 60000);
        set("nkgain", 250);

	set_skill("unarmed",1100);
        set_skill("dodge",1100);
        set_skill("parry",1100);
        set_skill("spells",1100);  
        set_skill("dao",1100);
        set_skill("literate",1100);
        set_skill("sword",1100);  
        set_skill("liangyi-sword",1100);
        set_skill("puti-zhi",1100);  
        set_skill("jindouyun",1100);
        set_skill("dodge",1100);
        set_skill("force",1100);   
        set_skill("wuxiangforce",1100);

        map_skill("spells", "dao");
        map_skill("unarmed", "puti-zhi");
        map_skill("force", "wuxiangforce");
        map_skill("sword", "liangyi-sword");
        map_skill("parry", "liangyi-sword");
        map_skill("dodge", "jindouyun");
        create_family("方寸山三星洞", 2, "弟子");

	set("inquiry", ([
                "book": "这里大多是我们道教经典，也有些平常书籍。",
		"千字文": (: borrow_me :),
		"道德经": (: borr_me :),
		"易传"	: (: yinyang_shu :),
        ]) );
	set("env/test","HIB");
	set_temp("armor_level",50+random(50));
	set_temp("weapon_level",50+random(50));
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"hand",1)->wear();
	carry_object(0,"sword",1)->wield();
}

string yinyang_shu()
{
	string name;
	int num;
	object book,me = this_player();
	if( me->query("family/family_name")!="方寸山三星洞" )
		return 0;
	if( me->is_knowing("puti_yinyang")>0 )
		return "你不是已经参悟了吗？";
	if( me->query_level()<8 )
		return "你还是安心修炼吧，这么高深的经书给你只能当枕头！";
	if( me->query("family/songguo_ok") )
	{
		book = new("/d/lingtai/obj/taijibook");
		if( book->move(me) )
		{
			book->set("owner_id",me->query("id"));
			me->delete("family/songguo_ok");
			EMOTE_D->do_emote(this_object(), "ok",geteuid(me),CYN,0,0,0);
			message_vision("$N将"+book->name()+"交给了$n。\n",this_object(),me);
			return "此乃易传真迹残本拓片，你且拿去参悟参悟。";
		}
		else
		{
			destruct(book);
			return "你真的想要吗？想要你就说嘛。。。";
		}	
	}
	if( me->query("family/songguo_num")>0 )
		return "我要的松果呢？";
			
	num = me->query_level();
	num/= 10;
	num = num/3*3;
	if( num<3 )
		num = 3;
	if( num>9 )
		num = 9;
	name = ({"金","金","金","黑","白","金","金",})[random(7)];
	name = name+"松果";
	me->set("family/songguo_num",num);
	me->set("family/songguo_name",name);
	return "我这人最爱吃松果了，你去给我寻来"+chinese_number(num)+"个"+name;
}	

int borr_me(object ob)
{       object m;
        ob = this_player();
        if ((string)this_player()->query("family/family_name")=="方寸山三星洞") {
                if ( this_player()->query("pending/book")) {
			message_vision("$N对$n说：上次借的还没还，怎么好再借给你呢？\n", this_object(), ob);
                	return 1;
		}
		if( (int)this_player()->query_skill("literate", 1) < 10 ) {
			message_vision("$N对$n说：你读书写字太差，借给你恐怕也看不懂啊。\n", this_object(), ob);
			return 1;
		}
		if ( time()<(int)this_object()->query("daode")+1800 ) {
			message_vision("$N一拱手，说：刚借出去，待会再来吧！\n", this_object());
			return 1;
		}
                m=new("/d/obj/book/daode");
                m->move(ob);
                ob->set("pending/book", 1);
		this_object()->set("daode",time());
		message_vision("$N从架上拿下本书来递给$n，说：记住要还唷！\n", this_object(), ob);
                return 1;
        }
	message_vision("$N说：我们这里的书不外借！\n", this_object());
	return 1;
}

int borrow_me(object ob)
{	object m;
	ob = this_player();
        if ((string)this_player()->query("family/family_name")=="方寸山三星洞") 
        {
                if ( this_player()->query("pending/book")) {
                        message_vision("$N对$n说：上次借的还没还，怎么好再借给你呢？\n", this_object(), ob);
                        return 1;
                }
		if( (int)this_player()->query_skill("literate", 1) < 10 ) {
                        message_vision("$N对$n说：你读书写字太差，借给你恐怕也看不懂啊。\n", this_object(), ob);
                        return 1;
                }

                if ( time()<(int)this_object()->query("qian")+1800 ) {
                        message_vision("$N一拱手，说：刚借出去，待会再来吧！\n", this_object());
                        return 1;
                }
                m=new("/d/obj/book/qian");
                m->move(ob);
                ob->set("pending/book", 1);
                this_object()->set("qian",time());
                message_vision("$N从架上拿下本书来递给$n，说：记住要还唷！\n", this_object(), ob);
                return 1;
        }
        message_vision("$N说：我们这里的书不外借！\n", this_object());
        return 1;

}

int accept_object(object who,object ob)
{
	object book;
	if( who->query("family/songguo_name")
	 && who->is_knowing("puti_yinyang")<=0 ) 
	{
		if( base_name(ob)=="/d/lingtai/obj/guo2" )
		{
			if( ob->query("name")==who->query("family/songguo_name") )
			{
				say("广羲子哈哈笑了几声，不错不错，就是要的这个！\n");
				who->add("family/songguo_num",-1);
				if( who->query("family/songguo_num")>0 )
				{
					EMOTE_D->do_emote(this_object(), "zeze",geteuid(who),CYN,0,0,0);
					say("广羲子呵呵笑道：不够不够，还差"+chinese_number(who->query("family/songguo_num"))+"个。\n");
				}
				else
				{
					who->delete("family/songguo_name");
					who->delete("family/songguo_num");
					who->set("family/songguo_ok",1);
					EMOTE_D->do_emote(this_object(), "great",geteuid(who),CYN,0,0,0);
					say("广羲子哈哈笑了几声，不错不错，不多也不少。\n");
					book = new("/d/lingtai/obj/taijibook");
					if( book->move(who) )
					{
						book->set("owner_id",who->query("id"));
						who->delete("family/songguo_ok");
						EMOTE_D->do_emote(this_object(), "ok",geteuid(who),CYN,0,0,0);
						message_vision("$N将"+book->name()+"交给了$n。\n",this_object(),who);
						say("广羲子捻了捻长须，说道：此乃易传真迹残本拓片，你且拿去参悟参悟。\n");
					}
					else	destruct(book);
				}
				return 1;	
			}
		}
	}
       	if(ob->query("id")=="qian") 
       	{
 		if ( this_player()->query("pending/book") )
 		{
			say("广羲子哈哈笑了几声，好借好还，再借不难！\n");
			who->set("pending/book", 0);
			this_object()->delete("qian");
		}
		else 	say("广羲子笑道：多谢，多谢！\n");
		return 1;
	}
	if (ob->query("id")=="daodejing") 
	{
        	if ( this_player()->query("pending/book") )
        	{
               		say("广羲子哈哈笑了几声，好借好还，再借不难！\n");
       			who->set("pending/book", 0); 
			this_object()->delete("daode");
		}
		else	say("广羲子笑道：多谢，多谢！\n");
                return 1;
	}
	if (ob->query("id")=="songguo") 
	{
		say("广羲子笑道：多谢，多谢！我最爱吃了！\n");
		who->set("pending/book", 0);
               	return 1;
	}
	else	return 0;
}

void attempt_apprentice(object ob)
{
        if( ob->query("class")=="bonze" )
        {
		EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：我们方寸山虽是有教无类，但是偏偏不收秃驴！哼！\n"NOR);
           	return ;
        }
        if( ob->query_level()<40 )
        {
		EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你还是先练好基本功再来！\n"NOR);
           	return ;
        }
        if( ob->query("class")!="taoist" )
        {
        	if( !ob->query_temp("pendding/fc_class") )
        	{
			EMOTE_D->do_emote(this_object(), "hmm",geteuid(ob),CYN,0,0,0);
           		tell_object(ob,CYN+name()+CYN"说道：你乃带艺拜师，还是先向祖师爷打听师门试炼一事吧。\n");
           		return ;
        	}
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们方寸山发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","三星洞方寸山又多了一个弟子  "+ob->name(1)+HIW"\n                                 方寸山的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "taoist");
}