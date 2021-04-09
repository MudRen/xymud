inherit ROOM;
#include <ansi.h>
#include "sea.h"

nosave object tieguaili = 0;
nosave object hanzhongli = 0;
nosave object ludongbin = 0;
nosave object zhangguolao = 0;
nosave object caoguojiu = 0;
nosave object hanxiangzi = 0;
nosave object lancaihe = 0;
nosave object hexiangu = 0;

void create ()
{
  	set("short", "大海");
  	set("long", @LONG
茫茫大海望不到边际。海面上波涛汹涌，几丈高的浪头此
起彼伏，象是要吞灭一切敢于到海上的东西。
    也许这里便是路的尽头，面前的大海对一个凡人来说是不
可逾越的。

LONG);
	setup();
}

object random_baxian()
{
	switch(random(7))
	{
		case 0 : return tieguaili;
		case 1 : return hanzhongli;
		case 2 : return ludongbin;
		case 3 : return zhangguolao;
		case 4 : return caoguojiu;
		case 5 : return hanxiangzi;
		default : return lancaihe;
	}
}

void fight12()
{
	string str;
	object me,npc;
	me = query("owner");
	if( !me )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		remove_call_out("fight8");
		remove_call_out("fight9");
		remove_call_out("fight10");
		remove_call_out("fight11");
		remove_call_out("fight12");
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		remove_call_out("fight8");
		remove_call_out("fight9");
		remove_call_out("fight10");
		remove_call_out("fight11");
		remove_call_out("fight12");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}	
	
	set("short","龙宫大门");
	str = @LONG
嵌在宫殿各处的珍宝发出的光芒耀得你连眼睛都睁不开了。依
稀看到宫门上方挂这一幅方匾，上有＂东海龙宫＂四个大字。

LONG;
	str+= "    这里明显的出口是 "HIG"west"NOR"。\n";
	set("long",str);
	message_vision("诸人不敢怠慢，紧紧跟随着杀向龙宫。\n\n",me);	
	npc = new(__DIR__"haishe");
	npc->move(this_object());
	me->command("look");
	message_vision("\n只见龙宫大门紧闭，宫门前守卫全无，只有一些海蛇在游来游去，不禁让人生疑。\n\n",me);
}

void fight11()
{
	tell_room(this_object(),HIY"\n那章鱼见势不妙，不得不现了原形！\n"NOR);
	tell_room(this_object(),"原来却是东海龙表弟所变化！\n");
	tell_room(this_object(),CYN"龙表弟说道：嘿嘿，道家八仙也不过如此。\n"NOR);
	tell_room(this_object(),HIY"龙表弟手捻口诀，念动真言，摇身一变，变得和海蛇一模一样！\n\n"NOR);
	tell_room(this_object(),"海蛇向东游去。\n");
	remove_call_out("fight11");
	remove_call_out("fight12");
	call_out("fight12",2+random(3));
}

void fight10()
{
	int damage;
	string str;
	object me,npc;
	me = query("owner");
	if( !me )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		remove_call_out("fight8");
		remove_call_out("fight9");
		remove_call_out("fight10");
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		remove_call_out("fight8");
		remove_call_out("fight9");
		remove_call_out("fight10");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}	
	
	message_vision("$N怒极，忿忿地将手中宝剑狠狠劈向礁石！\n结果砍得火星四溅，没有任何反应，$N恼得火冒头顶。\n",ludongbin);
	EMOTE_D->do_emote(tieguaili, "falcon",0,CYN,0,0,0);
	tieguaili->command("say 莫恼莫恼！待我来收拾它！");
	message_vision("$N口中念念有词，举起手中铁杖，一杖就打将下去！\n不料却又打在一堆软肉里！原来那礁石又化作了一只巨大的八脚章鱼！\n",tieguaili);
	if( random(4)==2 )
	{
		message_vision("一边的$N眼明手快，将手中竹篮祭将出去，朝向大章鱼就罩了过去！\n",lancaihe);
		remove_call_out("fight9");
		remove_call_out("fight10");
		call_out("fight11",2+random(3));
		return;
	}
	else
	{
		message_vision("好一个八脚的水精，浑身灵活的缩成一团，飞快的就隐到了大海深处，临跑前还不忘给$N来了狠狠的一击！\n",me);
		damage = 590+random(500);
		me->receive_wound("kee",damage);
		COMBAT_D->report_status(me,1);
		me->set_temp("death_msg","被大章鱼打死了！");
		remove_call_out("fight9");
		remove_call_out("fight10");
		call_out("fight9",2+random(3));
	}
}

void fight9()
{
	int damage;
	string str;
	object me,npc;
	me = query("owner");
	if( !me )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		remove_call_out("fight8");
		remove_call_out("fight9");
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		remove_call_out("fight8");
		remove_call_out("fight9");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}	
	
	message_vision("\n\n海里突然窜出一条巨鲸，张开闸门般的大口吞下诸人！\n",me);
	if( random(5)==3 )
	{
		message_vision("只见$N不慌不忙，吹起了手中的仙笛。那笛声悠扬悦耳，巨鲸听了，顿时浑身酥软，瘫倒在地，却原来是一块礁石。\n\n",hanxiangzi);
		remove_call_out("fight9");
		remove_call_out("fight10");
		call_out("fight10",2+random(3));
		return;
	}
	else
	{
		message_vision("诸人慌忙闪开，忙乱中，$N被鲸鱼扯掉了一块皮肉，疼的黄豆般的汗滴哗哗直落。\n",me);
		damage = 590+random(500);
		me->receive_wound("kee",damage);
		COMBAT_D->report_status(me,1);
		message_vision("\n\n巨鲸将大尾一摆，又窜到大海深处去了。\n\n",me);
		me->set_temp("death_msg","被巨鲸吞进了肚子！");
		remove_call_out("fight9");
		call_out("fight9",2+random(3));
	}
}

void fight8()
{
	string str;
	object me,npc;
	me = query("owner");
	if( !me )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		remove_call_out("fight8");
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		remove_call_out("fight8");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}	
	
	set("short","海底");
	str = @LONG
前方隐约现出一座宫殿，发出一道道五颜六色的光芒。这里的
鱼儿也特别多，还有许多奇形怪状的海怪。一行行，一列列，宛如
臣子拜见皇帝一般。

LONG;
	str+= "    这里明显的出口是 "HIG"southwest"NOR" 和 "HIG"east"NOR"。\n";
	set("long",str);
	message_vision("诸人齐头并进，再次杀向水晶宫。\n\n",me);
	me->command("look");
	remove_call_out("fight9");
	call_out("fight9",2+random(5));	
}

void fight7()
{
	object me,npc;
	me = query("owner");
	if( !me )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		remove_call_out("fight7");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}	
	message_vision("\n诸神仙齐声道：好好好，打得好。\n",me);
	npc = random_baxian();
	if( !npc )
		npc = ludongbin;
	npc->command("say 一鼓作气，将这东海搅个天翻地覆，不交出何仙姑誓不罢休！");
	npc = random_baxian();
	if( !npc )
		npc = lancaihe;
	EMOTE_D->do_emote(npc, ({"addoil","support","comeon",})[random(3)],0,CYN,0,0,0);
	remove_call_out("fight7");
	remove_call_out("fight8");
	call_out("fight8",2+random(3));
}

void fight6()
{
	object me,npc;
	me = query("owner");
	if( !me )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		remove_call_out("fight5");
		remove_call_out("fight6");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}	
	
	npc = new(__DIR__"xiejiang");
	npc->set_skills(me->query_level());
	npc->move(this_object());
	message_vision("\n\n一群蟹将从海底冲了出来，拦住了去路！\n",me);
	npc->kill_ob(me);	
}

void fight5()
{
	remove_call_out("fight5");
	remove_call_out("fight6");
	call_out("fight6",2+random(5));
}

void fight4()
{
	object me,npc;
	me = query("owner");
	if( !me )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("fight3");
		remove_call_out("fight4");
		remove_call_out("fight2");
		remove_call_out("fight1");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}	
	npc = new(__DIR__"xiabing");
	npc->set_skills(me->query_level());
	npc->move(this_object());
	message_vision("\n\n一群虾兵从海底冲了出来，拦住了去路！\n",me);
	npc->kill_ob(me);
}
	
void fight3()
{
	string str;
	object me,npc;
	set("short","海底");
	str = @LONG
到了一个水中世界。海面上波浪汹涌，这里却静得出奇。一群
群银色的小鱼在蓝色的海水中游来游去，脚下是色彩斑斓的珊湖礁，
其中白色的珊瑚连成一线，如一条白云铺成的道路。

LONG;
	str+= "    这里明显的出口是 "HIG"up"NOR" 和 "HIG"east"NOR"。\n";
	set("long",str);
	npc = random_baxian();
	if( !npc )
		npc = ludongbin;
	message_vision("$N掐指念咒，对着海水一指，顿时波涛一分，众人齐齐杀向东海龙宫。\n",npc);
	me = query("owner");
	if( !me )
	{
		remove_call_out("fight3");
		remove_call_out("fight2");
		remove_call_out("fight1");
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("baxian_sing");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}	
	me->command("look");
	remove_call_out("fight4");
	call_out("fight4",3);
}

void fight2()
{
	string str;
	object me,npc;
	npc = random_baxian();
	if( !npc )
		npc = tieguaili;
	message_vision("\n众人一阵忙乱之后， $N慌忙检点人数。\n",npc);
	EMOTE_D->do_emote(npc, ({"?","hmm","why",})[random(3)],0,CYN,0,0,0);
	npc->command("say 奇怪奇怪，怎么人数不对？");
	ludongbin->command("say 何仙姑呢？");
	message_vision("$N低头掐指算了算，大吃一惊：又是那东海龙宫！\n",tieguaili);
	npc = random_baxian();
	if( !npc )
		npc = ludongbin;
	message_vision(CYN"$N说道：走走走，一起去龙宫救何仙姑。\n"NOR,ludongbin);	
	remove_call_out("fight3");
	call_out("fight3",3);
}

void fight1()
{
	int damage;
	string str;
	object who,*inv;
	CHANNEL_D->do_channel(this_object(),"rumor","听说龙表弟被海中一位桃脸杏腮，楚楚动人的妙龄女郎给迷住了心思。");
	str = "\n\n平静的海面突然掀起了一个浪头，结果$N一个不留神，被巨浪打了个正着，弄了个浑身湿透！\n";
	inv = all_inventory();
	who = inv[random(sizeof(inv))];
	message_vision(str,who);
	damage = 490+random(500);
	who->receive_wound("kee",damage);
	COMBAT_D->report_status(who,1);
	hexiangu->move(__DIR__"sea3");
	remove_call_out("fight1");
	remove_call_out("fight2");
	call_out("fight2",3);
}

void baxian_sing()
{
	int v;
	object me,npc,*inv = all_inventory();
	if( !query("fighting") )
	{
		tell_room(this_object(),HIC"\n\n好个八仙过东海，风清清，白鹭戏晴空，浪滔滔，金龙游碧海．一行人谈笑饮酒，好不快活！\n"NOR);
		npc = inv[random(sizeof(inv))];
		if( !userp(npc) && npc->query("name")!="小毛驴" )
			npc->donghai();
		me = query("owner");
		if( !me )
		{
			remove_call_out("baxian_sing");
			REMOVE_D->add_room(this_object(),1);
			return;
		}
		if( !living(me) || !present(me,this_object()) )
		{
			remove_call_out("baxian_sing");
			tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
			REMOVE_D->add_room(this_object(),1);
			return;
		}
		me->add_temp("pendding/wzg_baxian_P",1);
		tieguaili = me->query_temp("pendding/wzg_baxian1");
		hanzhongli = me->query_temp("pendding/wzg_baxian2");
		ludongbin = me->query_temp("pendding/wzg_baxian3");
		zhangguolao = me->query_temp("pendding/wzg_baxian4");
		caoguojiu = me->query_temp("pendding/wzg_baxian5");
		hanxiangzi = me->query_temp("pendding/wzg_baxian6");
		lancaihe = me->query_temp("pendding/wzg_baxian7");
		hexiangu = me->query_temp("pendding/wzg_baxian8");		
		v = me->query_temp("pendding/wzg_baxian_P");
		if( random(v)>=5 )
		{
			set("fighting",1);
			remove_call_out("fight1");
			call_out("fight1",1+random(5));
			return;
		}
		remove_call_out("baxian_sing");
		call_out("baxian_sing",1+random(5));
	}	
}

void init()
{
	if( !userp(this_player()) 
	 || this_player()!=query("owner") )
		return;
	remove_call_out("baxian_sing");
	call_out("baxian_sing",1+random(5));
}

void finish3(object me)
{
	if( !me )
	{
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("baxian_sing");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	message_vision("\n\n众人但觉一阵败兴，也断了东游的兴致。\n\n",me);
	message_vision("$N说道：既然如此，便散去了吧。\n$N踩着大葫芦腾空而起，回转五庄观去了。\n\n",tieguaili);
	destruct(tieguaili);
	message_vision("众人扫兴，皆相继离去。\n",me);
	destruct(hanzhongli);
	destruct(ludongbin);
	if( zhangguolao->query_temp("ridee") )
		destruct(zhangguolao->query_temp("ridee"));
	destruct(zhangguolao);
	destruct(caoguojiu);
	destruct(hanxiangzi);
	destruct(lancaihe);
	hexiangu->command("say 咦？怎么说走就走了？");
	EMOTE_D->do_emote(hexiangu, "thank",geteuid(me),CYN,0,0,0);
	message_vision("$N也急急忙忙的离去了。\n",hexiangu);
	me->set_temp("pendding/fc_visite_baxianguohai",1);
	me->delete_temp("pendding/wzg_baxian_P");
	me->delete_temp("pendding/fc_wzgask");
	me->delete_temp("pendding/wzg_askob");
	delete("owner");
	tell_object(me,HIY"【灵台观礼】八仙过海已告一段落，还是再去找龙王与镇元大仙，询问「灵台观礼」一事吧。\n"NOR);
	me->move("/d/changan/eastseashore");
	REMOVE_D->add_room(this_object(),1);
	return;
}

void finish2(object me)
{
	if( !me )
	{
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("baxian_sing");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	message_vision("\n\n龙宫大门一开，何仙姑从内走了出来。\n\n",me);
	hexiangu->move(this_object());
	EMOTE_D->do_emote(hexiangu, "wanfu",0,CYN,0,0,0);
	lancaihe->command("say 妹纸！有没受什委屈？！");
	EMOTE_D->do_emote(hexiangu, "shy",geteuid(hexiangu),CYN,0,0,0);
	ludongbin->command("say 此话怎说？");
	hexiangu->command("say 此地安，不思蜀。。。。");
	tieguaili->command("say ......");
	hanzhongli->command("say ......");
	ludongbin->command("say ......");
	zhangguolao->command("say ......");
	caoguojiu->command("say ......");
	hanxiangzi->command("say ......");
	lancaihe->command("say ......");
	remove_call_out("finish2");
	remove_call_out("finish3");
	call_out("finish3",2+random(4),me);
}

void finish()
{
	string str;
	object me,npc;
	remove_call_out("fight1");
	remove_call_out("fight2");
	remove_call_out("fight3");
	remove_call_out("fight4");
	remove_call_out("fight5");
	remove_call_out("fight6");
	remove_call_out("fight7");
	remove_call_out("fight8");
	remove_call_out("fight9");
	remove_call_out("fight10");
	remove_call_out("fight11");
	remove_call_out("fight12");
	me = query("owner");
	if( !me )
	{
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	if( !living(me) || !present(me,this_object()) )
	{
		remove_call_out("baxian_sing");
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		REMOVE_D->add_room(this_object(),1);
		return;
	}
	message_vision("龙表弟鼻青脸肿的就地求饶。\n\n",me);
	lancaihe->command("say 哼！你说，你把何家妹纸藏到哪里去了？！\n");
	EMOTE_D->do_emote(ludongbin, "hmm",0,CYN,0,0,0);
	caoguojiu->command("say 直娘贼！你是不是又看上何仙姑的美貌，意图不轨？！\n");
	message_vision(CYN"龙表弟说道：几位爷爷饶命，小的一时糊涂，掉了节操，仙姑虽然被绑在了龙宫，不过她如今好吃好住，啥损失也没有。\n"NOR,me);
	EMOTE_D->do_emote(lancaihe, "sweat",0,CYN,0,0,0);
	EMOTE_D->do_emote(caoguojiu, "sweat",0,CYN,0,0,0);
	EMOTE_D->do_emote(lancaihe, "hmm",geteuid(caoguojiu),CYN,0,0,0);
	tieguaili->command("say 好好好，废话少说，快些放人！\n");
	message_vision("龙表弟急急忙忙的离开了。\n",me);
	remove_call_out("finish2");
	call_out("finish2",2+random(4),me);
}