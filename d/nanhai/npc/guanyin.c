inherit SUPER_NPC;
#include <ansi.h>

string begin_go();

mapping Book = ([
	"〖刀法入门〗"	: ({"这是长安城里三联书局的刀法入门！","/d/obj/book/blade_1","blade"}),
	"〖拳法入门〗"	: ({"这是长安城里三联书局的拳法入门！","/d/obj/book/unarmed_1","unarmed",}),
	"〖道德经〗"	: ({"这是车迟国三清观内藏经楼的道德经还是灵台方寸山的经阁中的收藏呢？", "/d/obj/book/daode","daode",}),
	"〖伏魔山心经〗": ({"这本〖伏魔山心经〗蕴含着求书者不少的心血,得来这本书着实不易！","/d/obj/book/forcebook","force",}),
	"〖女儿经〗"	: ({"这本〖女儿经〗在月宫练功房乃为其女弟子读书识字之用！","/d/obj/book/girlbook","moon",}),
	"〖青莲剑谱〗"	: ({"这是诗仙之物,只怕是用桂花酒换来的！","/d/obj/book/jianpu","libai",}),
     	"〖金刚经〗"	: ({"此乃我佛如来之大成佛法,一直留在南海普陀书院中！","/d/obj/book/jingang","putuo",}),
     	"〖旧书〗"	: ({"这是长安城东,望南街内的武学书籍,上面记载了刀，斧，叉，锤，锏，钯，枪，杖，棒，剑十种基本武功！","/d/obj/book/misc","changan",}),
	"〖无字天书〗"	: ({"此乃袁守诚处得来的法术要领！","/d/obj/book/nowords","yuan",}),
	"〖格斗秘诀〗"	: ({"你能帮助高员外除去强盗,品行可嘉！","/d/obj/book/parry_book","gao",}),
	"〖千字文〗"	: ({"是灵台方寸山广羲子道长手里的〖千字文〗吗？","/d/obj/book/qian","guang"}),
	"〖拳经〗"	: ({"这是长安武馆范青平所藏格斗技巧。","/d/obj/book/quanjing","fan",}),
	"〖三字经〗"	: ({"这〖三字经〗一书我南海普陀书院,长安书社以及月宫练功房都收有此书,当真是流传甚广。","/d/obj/book/san","san"}),
	"〖枪法简介〗"	: ({"这是大唐将军府内的藏书,记载了枪法的运用。","/d/obj/book/spearbook","spear",}),
	"〖杖法简要〗"	: ({"此乃我南海普陀书院之物。","/d/obj/book/staffbook","staff",}),
	"碎布头"	: ({"这碎布头沾满杀气,你为何因一身外之物大开杀戒？","/d/obj/book/stickbook","stick",}),
	"〖风水〗"	: ({"这是东海熬来国老妇人的家传书籍。","/d/obj/book/windwater","aolai",}),
]);

void create()
{
	set_name("观音菩萨", ({ "guanyin pusa", "guanyin", "pusa" }));
	set_level(169);
	create_family("南海普陀山", 1, "菩萨");
	set("title", "救苦救难大慈大悲");
	set("long", @LONG
理圆四德，智满金身。眉如小月，眼似双星。兰心欣紫竹，
蕙性爱得藤。她就是落伽山上慈悲主，潮音洞里活观音。
LONG);
	set("gender", "女性");
	set("age", 35);
	set("attitude", "peaceful");
	set("rank_info/self", "贫僧");
	set("rank_info/respect", "菩萨娘娘");
	set("class", "bonze");
	set("bonze/class","bonze");
	set("force_factor", 145);
	set("mana_factor", 150);

	set_skill("literate",1690);
	set_skill("spells",1690);
	set_skill("buddhism",1690);
	set_skill("unarmed",1690);
	set_skill("jienan-zhi",1690);
	set_skill("dodge",1690);
	set_skill("lotusmove",1690);
	set_skill("parry",1690);
	set_skill("force",1690);
	set_skill("lotusforce",1690);
	set_skill("staff",1690);
	set_skill("blade",1690);	
	set_skill("cibeidao",1690);	
	set_skill("lunhui-zhang",1690);
	map_skill("spells", "buddhism");
	map_skill("blade", "cibeidao");	
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("inquiry",([
      		"灵台观礼"    : (: begin_go :),
      		"净瓶": "前些天，福星借我的净瓶用，到现在也没有还，你去看看吧。" 
	]));
	set_skill("tianlong-chanchang",1690);
	set_skill("jingang-sanmei",1690);
	set_skill("jingang-zhenshen",1690);
	set_skill("longxiang-li",1690);
	set_skill("qu-yue",1690);
	set_skill("bubu-shenglian",1690);
	set_skill("liuli-xindeng",1690);
	
	setup();
	carry_object("/d/nanhai/obj/jiasha")->wear();
	carry_object("/d/nanhai/obj/nine-ring")->wield();
}

void die()
{
        if( environment() ) 
        {
        	message("sound", "\n\n观音菩萨摇头叹道：刚离迷障，又入魔障，世间疾苦，何人度之！\n\n", environment());
        	command("sigh");
        	message("sound", "\n观音菩萨驾祥云，登彩雾，径往西方去了。。。\n\n", environment());
        	lose_inventory();
	}
	destruct(this_object());
}

void unconcious()
{
	die();
}

void remove_book_data(object who)
{
	mixed *tmp,*temp;
	int i;
	if( !who )
		return;
	temp = values(Book);
	for(i=0;i<sizeof(temp);i++)
	{
		tmp = temp[i];
		who->delete_temp("pedding/putuo_book_"+tmp[2]);
	}	
}

varargs mixed check_book(object who,object obj)
{
	string *names,name,long,data,file;
	int i;
	
	if( !environment() )
		return 0;
	if( !who || !living(who) || !present(who,environment()) )
		return 0;
	if( !who->query_temp("pendding/fc_visite")
    	 || who->is_knowing("puti_panlong") )
    	 	return 0;
	if( !who->query_temp("pendding/fc_visite_putuobook") )
		return 0;
	if( who->query_temp("pendding/fc_visite_putuo") )
		return "你可是想向我询问「灵台观礼」一事？";
	if( obj )
	{
		name = obj->query("name");
		if( undefinedp(Book[name]) )
			return "这是啥子？";
		data = Book[name][2];
		long = Book[name][0];
		file = Book[name][1];
		if( who->query_temp("pedding/putuo_book_"+data) )
			return "这本书你已给过贫僧了。";
		if( base_name(obj)!=file )
			return "这本书名称虽然对，但不是我要的。";	
		return "DATA:"+data+"#"+long;
	}
	else
	{
		names = keys(Book);
		for(i=0;i<sizeof(names);i++)
		{
			name = names[i];
			long = Book[name][0];
			file = Book[name][1];
			data = Book[name][2];
			if( !who->query_temp("pedding/putuo_book_"+data) )
				return "我正准备去收集那"+name+"。";
		}
	}
	return 1;		
}	

int accept_object(object me,object ob)
{       
	mixed foo;
	string long,data,myname=RANK_D->query_respect(me), thing=(string)ob->query("id");
	object who;
        who=this_object();
      
	if( base_name(environment())!="/d/nanhai/chaoyindong" )
	{
		tell_object(me,CYN+name()+CYN"说道：此事待我回到珞珈山潮音洞再说。\n"NOR);
    		return 0;
    	}
    	foo = check_book(me,ob);
    	if( !foo || !stringp(foo) )
    		return 0;
    	if( sscanf(foo,"DATA:%s#%s",data,long)!=2 )
    	{
    		tell_object(me,CYN+name()+CYN"说道："+foo+"\n"NOR);
    		return 0;
    	}
    	me->set_temp("pedding/putuo_book_"+data,1);
    	tell_object(me,CYN+name()+CYN"说道："+long+"\n"NOR);
    	return 1;
}

void go_back()
{
	remove_call_out("go_back");
	if( !environment() )
		return;
	if( base_name(environment())=="/d/nanhai/chaoyindong" )
		return;
	message_vision("\n"HIC"观音菩萨道：观礼事毕，贫僧这就回转普陀，老祖所议之事，容贫僧考虑考虑。\n"NOR,this_object());
        message_vision(HIY"$N"HIY"口中念着佛号，脚下升起一朵莲花宝座，缓缓离地飞去……  \n"NOR,this_object());
	delete_temp("no_return");
	this_object()->move("/d/nanhai/chaoyindong");
	message_vision(HIG"\n忽听得空中有一阵异香仙乐，飘飘而来,空中飘落一朵七彩祥云，$N"HIG"拨开云端走了出来……\n"NOR,this_object());			
}

string begin_go()
{
	mixed foo;
	object me,ob;
    	int dx,wx,qn;
	me=this_player();
	ob=this_object();

    	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong") )
    		return 0;
    	if( base_name(environment())!="/d/nanhai/chaoyindong" )
    		return "此事待我回到珞珈山潮音洞再说。";
    	if( me->query_temp("pendding/fc_visite_putuo") )	
	{
        	message_vision(HIC"\n$N"HIC"道：既然"+RANK_D->query_respect(me)+ "来请,我们这就动身吧！\n"NOR,ob);
        	message_vision(HIY"$N"HIY"口中念着佛号，脚下升起一朵莲花宝座，缓缓离地飞去……  \n"NOR,ob);
        	ob->set_temp("no_reture",1);
		ob->move("/d/lingtai/inside1");
		message_vision(HIY"\n刹那间祥云缭绕，佛光万丈，莲花万朵，络绎不断，$N"HIY"踏着莲花宝座，徐徐降落尘间………\n"NOR,ob);
		remove_call_out("go_back");
    		call_out("go_back",2700);
        	return "我与老祖正好有事相商。";
	}
	if( !me->query_temp("pendding/fc_visite_putuobook") )
	{
		me->set_temp("pendding/fc_visite_putuobook",1);
		return "来的不凑巧,我正为收集东土大唐所有基本武学书籍忙碌,要去灵台观礼只怕没有空闲，唉。";
	}
	foo = check_book(me);	
	if( !foo )
		return 0;
	else if( stringp(foo) )
		return foo;
	else if( !intp(foo) )
		return 0;
	else if( foo!=1 )		
		return 0;
	else
	{
		remove_book_data(me);
		me->add_temp("pendding/fc_visited",1);
		me->set_temp("pendding/fc_visite_putuo",1);
		me->delete_temp("fc_visite_putuobook");
		me->delete_temp("pedding");
		CHANNEL_D->do_channel(this_object(),"chat",HIY+me->name()+HIC"助我收齐武学精要,届时贫僧一定上灵台观礼！"NOR);
		if( !me->query("mark/guanli_putuo") )
		{
			dx = ((me->query("daoxing")/1000)/10+1)*1000;
			if( dx>=81000) 
				dx = 81000;
			wx = dx+random(dx);	
			qn = 10000;			
			me->add("daoxing",dx);
			me->add("combat_exp",wx);
			me->add("potential",qn);
			tell_object(me,HIY"【灵台观礼】你得到了"+wx+"点武学经验、"+chinese_number(dx/1000)+"年道行以及"+qn+"点潜能的奖励！\n"NOR);
			me->set("mark/guanli_putuo",1);	
		}	
		tell_object(me,HIY"【灵台观礼】你已成功邀请到"+chinese_number(me->query_temp("pendding/fc_visited"))+"位圣贤参加灵台观礼。\n"NOR);
		if( me->query("family/family_name")=="方寸山三星洞")
			return "观礼之日还请" + RANK_D->query_respect(me) + "再来告知一声。";
		else	return "多谢多谢。";	
	}				
}
void attempt_apprentice(object ob)
{
        if( (string)ob->query("bonze/class")!="bonze" )
        {
        	EMOTE_D->do_emote(this_object(), "shake",geteuid(ob),CYN,0,0,0);
        	tell_object(ob,CYN+name()+CYN"说道：阿弥陀佛，贫僧只收佛家弟子，这位" +RANK_D->query_respect(ob) + "还是先去剃度吧。\n"NOR);
		return;
        }
        if( ob->query("class") && ob->query("class")!="bonze"
         && !ob->query("family/putuo_class_succ") )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：阿弥陀佛，施主是啥来头啊？还是先完成惠安的「带艺拜师」任务吧。\n"NOR);
		return;
	}
        if( ob->query_level()<125 )
        {
        	EMOTE_D->do_emote(this_object(), "shake",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是先下去打好基础再说。\n"NOR);
           	return ;
        }
        ob->delete("family/putuo_class_guai");
        ob->delete("family/putuo_class_succ");
	EMOTE_D->do_emote(this_object(), "nod",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们南海普陀山发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        {
		ob->set("class", "bonze");
		if( !ob->is_titles("观世音亲传弟子") )
		{
	 		if( ob->set_titles("观世音亲传弟子") )
	 		{
	 			tell_object(ob,HIC"【系统】你获得了称号：「"HIY"观世音亲传弟子"NOR HIC"」。\n"NOR);
	 			ob->save();
			}	
		}
	}
}