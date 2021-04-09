inherit SUPER_NPC;
#include <ansi.h>

int ask_mijue();
string begin_go();

string ask_zhen()
{
	object me = this_player();
	if( me->query("family/family_name")!="百花谷" 
	 || me->query("shilian")=="bhg" )
		return "此乃我百花的护派之阵。";
	if( me->query_level()<80 )
		return "你现在去我怕枉送了性命。";
	if( time()<me->query("maze/baihuazhen")+7200 )
		return "你不能频繁进入阵中。";
	me->delete_temp("maze");	
	if( MAZE_D->enter_maze(me, "baihuazhen") )
	{
		me->set_temp("maze/baihuazhen",1);
        	me->set("maze/baihuazhen",time());
        	return "小心为佳。";
	}		
	return "你还是歇歇再来。"; 	
}

void create()
{
	set_name("凝眸仙子", ({"ningmou xianzi", "ningmou", "xianzi"}));
	set_level(165);
	set("long",@LONG
百花谷主一直是个迷一样的人物，甚至仍然有人说她是仙子。大
约五十年前，一个采药的小童在林间迷路，在饥渴绝望的时刻，花丛
中翩翩飘下一美丽女子，为他指明了出去的道路。时间飞逝，当年的
小童也变成了白发老翁，但在他心中一直把当年救她的女子当成上天
派下来拯救他的仙子，因为她在花间飞舞那轻盈的身姿，根本就不象
凡人......。
LONG);
	create_family("百花谷", 1, "弟子");
	set("title", HIM"百花谷主"NOR);
       
	set("gender", "女性");
	set("age", 35);
	set("attitude", "friendly");
	set("rank_info/respect", "神仙");
	set("per", 30);
	set("int", 30);
	set("force_factor", 125);
	set("mana_factor", 100);
	set_skill("literate", 1650);
	set_skill("unarmed", 1650);
	set_skill("dodge", 1650);
	set_skill("force", 1650);
	set_skill("parry", 1650);
	set_skill("sword", 1650);
	set_skill("spells", 1650);
	set_skill("zongheng-sword",1650);
	set_skill("baihua-xianfa", 1650);
	set_skill("rainbow-zhi", 1650);
	set_skill("brightjade-force", 1650);
	set_skill("siji-zhang", 1650);
	set_skill("wuyou-steps", 1650);
   	map_skill("spells", "baihua-xianfa");
   	map_skill("unarmed", "rainbow-zhi");
   	map_skill("force", "brightjade-force");
   	map_skill("dodge", "wuyou-steps");
   	map_skill("sword", "zongheng-sword");
   	map_skill("parry", "zongheng-sword");
   	set_skill("jiefeng",1650);
   	set_skill("hutian",1650);
   	set_skill("huakai-qingke",1650);
   	set_skill("butian-yuri",1650);
 	set("inquiry", ([
          	"纵横剑法": (: ask_mijue :),
          	"百花大阵": (: ask_zhen:),
          	"灵台观礼": (: begin_go :),
	]));
 	set("env/test",({"HIM","HIB"})[random(2)]);
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"sword",1)->wield();
	powerup(1,1);
}

void attempt_apprentice(object ob)
{
	if( ob->query_level()<125 )
        {
        	EMOTE_D->do_emote(this_object(), "addoil",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是去先打好基础。\n"NOR);
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
        if( !ob->query("shilian") && ob->query("shilian")!="bhg" )
        {
        	EMOTE_D->do_emote(this_object(), "smile",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：入我门下，需得过了本仙子的「百花大阵」才行。\n"NOR);
           	return ;
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们百花谷发扬光大。\n"NOR);
	CHANNEL_D->do_channel(this_object(),"rumor","听说"HIG"百花谷主"HIM"近日又新收了一门弟子！"NOR);
	command("recruit " + geteuid(ob) );
	return;
}

int ask_mijue()
{ 
	int i;
	object book;
        object me=this_player();
	
	if(me->query("family/family_name")!= "百花谷")        
	{
	        message_vision("\n$N对$n摇了摇头。\n"NOR,this_object(),me);
        	return 1;
	}
	if( (int)me->query_level()<25 )
	{
		message_vision("\n$N对$n说道：多年前本门一不肖弟子盗出本门纵横剑法秘籍出谷后就不知所踪。\n可惜你武功不够，$N深深叹了口气。\n"NOR,this_object(),me);
        	return 1;
	}
	if( time()<me->query("family/zongheng_give")+3600 )
	{
		say(CYN+name()+CYN"说道：你不是刚刚要过吗？\n"NOR);
		return 1;
	}
	if( me->is_knowing("bhg_zongheng")>0 )
        {
        	message_vision(HIC"\n$N对$n说道：多谢你帮本门找回秘籍。\n"NOR,this_object(),me);
        	if( me->query_temp("zongheng_book") != "given")
		{
        		book=new("/d/obj/book/zongheng");
        		book->move(me);
			me->set("family/zongheng_give",time());
		}
		me->delete_temp("bhg/ask");
        	return 1;
        }
	else if( me->query_temp("bhg/ask") == 1)
	{ 
		message_vision("凝眸仙子对$N说道：你已经领过任务了，快去完成吧。\n"NOR,me);
		return 1;
	}
	message_vision("\n$N悄悄对$n说道：前几天本门一不肖弟子盗出本门纵横剑法秘籍出谷后就不知所踪。\n据说最近他逃窜到了百花谷外。\n",this_object(),me);
	book=new("/d/baihuagu/npc/dizi");
	if( !book->information(me) )
	{
		message_vision("\n$N对$n说道：不放心让你去。\n"NOR,this_object(),me);
        	return 1;
	}
        book->set("owner_id",me->query("id"));
        book->set("title",me->name()+"追杀的");
       	book->move("/d/penglai/baihuagu"+random(5));
        me->set_temp("bhg/ask",1);
        return 1;
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

int recruit_apprentice(object ob)
{
	 if( ::recruit_apprentice(ob) )
	 {
	 	ob->set("class","xian");
	 	if( ob->set_titles("凝眸仙子亲传弟子") )
		{
	 		tell_object(ob,HIC"【系统】你获得了称号：「"HIM"凝眸仙子亲传弟子"NOR HIC"」。\n"NOR);
	 		ob->save();
	 	}
	 }	
}

void go_back()
{
	remove_call_out("go_back");
	if( !environment() )
		return;
	if( base_name(environment())=="/d/baihuagu/huahai1" )
		return;
	message_vision("\n"HIC"凝眸仙子道：观礼事毕，本仙子这就回转百花谷，老祖所议之事，容我考虑考虑。\n"NOR,this_object());
        message_vision(HIY"只见$N"HIY"手指一扬，纷纷花瓣有如花雨落下，$P的身形也渐渐消失在花雨中.....\n"NOR,this_object());
	delete_temp("no_return");
	this_object()->move("/d/baihuagu/huahai1");
	message_vision(HIY"\n随着一阵花香飘过，$N"HIY"的身影出现在一阵花雨中.....\n"NOR,this_object());			
}

string begin_go()
{
	mapping temp;
	mixed *files,*obj;
	object room,gui,me,ob;
	int dx,wx,qn,i;
    	
    	me=this_player();
	ob=this_object();
	
	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong") )
    		return 0;
    	if( base_name(environment())!="/d/baihuagu/huahai1" )
    		return "此事待本仙子回谷后再议。";
	if( me->query_temp("pendding/fc_visite_bhg") )
	{
        	message_vision("\n"HIC"凝眸仙子道：" + RANK_D->query_respect(me) + "本仙子即刻赴灵台之约！\n"NOR,me);
        	message_vision(HIY"只见$N"HIY"手指一扬，纷纷花瓣有如花雨落下，$P的身形也渐渐消失在花雨中.....\n"NOR,ob);
        	ob->set_temp("no_return",1);
    		ob->move("/d/lingtai/inside1");
    		message_vision(HIY"\n随着一阵花香飘过，$N"HIY"的身影出现在一阵花雨中.....\n"NOR,ob);
    		remove_call_out("go_back");
    		call_out("go_back",2700);
		return "我与老祖正好有事相商。";
	}
	if( !me->query_temp("pendding/fc_visite_bhggive") )
		return "我正在收集天下百花，天下名花越多，据本门古籍记载，酿出的百花酿越是醇香。";
	me->set_temp("pendding/fc_visite_bhg",1);
	me->delete_temp("pendding/fc_visite_bhggive");
	me->add_temp("pendding/fc_visited",1);
	CHANNEL_D->do_channel(this_object(),"chat",HIY+me->name()+HIC"助我酿制"HIM"百花珍酿"HIC",届时本仙子一定上灵台观礼！"NOR);
	if( !me->query("mark/guanli_bhg") )
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
		me->set("mark/guanli_bhg",1);
	}	
	tell_object(me,HIY"【灵台观礼】你已成功邀请到"+chinese_number(me->query_temp("pendding/fc_visited"))+"位圣贤参加灵台观礼。\n"NOR);
	if( me->query("family/family_name")=="方寸山三星洞")
		return "观礼之日还请" + RANK_D->query_respect(me) + "再来告知一声。";
	else	return "多谢多谢。";	
}

int accept_object(object me,object obj)
{
	string name,*Flowers = ({
		HIB"蓝玫瑰"NOR,HIB"黑郁金香"NOR,HIB"野风信子"NOR,HIB"玉白露"NOR,HIB"睡芙蓉"NOR,
		MAG"梦幻玫瑰"NOR,HIC"幻梦幽兰"NOR,HIB"薄雪花"NOR,HIG"风野玫"NOR,HIR"美人血"NOR,
		HIW"青凰玫"NOR,HIB"紫蔷薇"NOR,HIB"大丽花"NOR,HIB"白玫瑰"NOR,HIB"翡翠绿"NOR,
		HIB"雪腊梅"NOR,HIB"曼陀罗"NOR,HIB"睡莲"NOR,HIR"红玫瑰"NOR,HIW"白玫瑰"NOR,
		HIM"粉风信子"NOR,HIG"情人草"NOR,MAG"熏衣草"NOR,HIC"蝴蝶兰"NOR,HIR"火百合"NOR,
		HIG"马蹄莲"NOR,HIW"满天星"NOR,HIM"粉金鱼草"NOR,HIC"天堂鸟"NOR,HIB"勿忘我"NOR,
		HIY"黄康乃馨"NOR,HIM"紫丁香"NOR,MAG"紫郁金香"NOR,
	});
	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong") )
    		return 0;
    	if( me->query_temp("pendding/fc_visite_bhggive") )
    		return 0;
	name = obj->query("name");	
	if( member_array(name,Flowers)==-1 )
		return 0;
	if( query_temp("flower_from_"+me->query("id")) )
	{	
		if( member_array(name,query_temp("flower_from_"+me->query("id")))!=-1 )
		{
			tell_object(me,CYN+query("name")+CYN"说道：这朵花你已经给过了。\n"NOR);
			return 0;
		}
	}	
	if( !query_temp("flower_from_"+me->query("id")) )
		set_temp("flower_from_"+me->query("id"),({name}));
	else	add_temp("flower_from_"+me->query("id"),({name}));
	EMOTE_D->do_emote(this_object(), ({"touch","thank","zeze","great"})[random(4)],geteuid(me),CYN,0,0,0);
	tell_object(me,CYN+query("name")+CYN"说道：这朵花我收下了，如果你觉得时机到了，就提醒我酿花(niang)吧。\n"NOR);
	return 1;
}

void init()
{
	::init();
	add_action("do_niang","niang");
}

void niang_hua(object me,string id,int n)
{
	string name;
	mixed *strs;
	remove_call_out("niang_hua");
	if( !me || !living(me) || !present(me,environment())
	 || !environment() || base_name(environment())!="/d/baihuagu/huahai1" )
	{
		this_object()->start_busy(1);
		delete_temp("flower_from_"+id);
		if( environment() )
			message("vision",name()+"叹了口气，停住了酿花。\n",environment());
		if( me )
			tell_object(me,HIY"【灵台观礼】因为你不在场，凝眸仙子不再帮你酿花。\n"NOR);
		return;				
	}
	strs = query_temp("flower_from_"+id);
	if( !strs || !arrayp(strs) || sizeof(strs)<1 )
	{
		n = (me->query_kar()/10+1)+n;
		n/= 2;
		if( random(n)<3 )
		{
			tell_room(environment(),"\n\n隐隐约约传来一丝清香，你尚未仔细品味，香气却已一闪而没！\n\n");
			this_object()->start_busy(1);
			delete_temp("flower_from_"+id);
			message_vision("$N朝$n叹了口气：奈何奈何，造化不够。\n",this_object(),me);
			tell_object(me,HIY"【灵台观礼】因为造化不够，凝眸仙子不再帮你酿花，重新来过吧。\n"NOR);
			return;		
		}
		else
		{
			tell_room(environment(),"\n\n隐隐约约传来一丝清香，你仔细品味，只觉香气愈来愈浓郁。\n\n");
			this_object()->start_busy(1);
			delete_temp("flower_from_"+id);
			EMOTE_D->do_emote(this_object(), "smile",geteuid(me),CYN,0,0,0);
			me->set_temp("pendding/fc_visite_bhggive",1);
			tell_object(me,HIY"【灵台观礼】你帮凝眸仙子收集百花，并成功酿出了百花珍酿，赶紧再次向她打听「灵台观礼」事宜吧。\n"NOR);
			return;		
		}
	}
	if( n==0 )
		message_vision(HIC"\n\n$N"HIC"掐指念咒，唤出一盏宝气氤氲的玉皿。\n"NOR,this_object());
	else	tell_room(environment(),"\n\n隐隐约约传来一丝清香，你仔细品味，只觉香气愈来愈浓郁。\n\n");	
	name = strs[random(sizeof(strs))];
	strs-= ({name});
	strs-= ({0});
	set_temp("flower_from_"+id,strs);
	message_vision(HIC"$N"HIC"掏出一株"+name+HIC"投至玉皿中，顿时一股香气弥漫开来。\n"NOR,this_object());
	this_object()->start_busy(10);
	n++;
	call_out("niang_hua",3+random(5),me,id,n);
}

int do_niang()
{
	object me = this_player();
	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong") )
    		return 0;
    	if( me->query_temp("pendding/fc_visite_bhggive") )
    		return 0;
	if( !query_temp("flower_from_"+me->query("id")) )
		return err_msg(name()+"疑惑的看着你：你没有给我花啊。\n");
	if( this_object()->is_busy() || this_object()->is_fighting() )
		return err_msg("她现在正忙着呢。\n");
	message_vision("$N向$n一作揖：烦请仙子替我酿百花。\n",me,this_object());
	EMOTE_D->do_emote(this_object(), "nod",geteuid(me),CYN,0,0,0);
	this_object()->start_busy(10);
	remove_call_out("niang_hua");
	call_out("niang_hua",1,me,me->query("id"),0);
	return 1;
}	
