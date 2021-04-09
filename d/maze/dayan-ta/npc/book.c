#include <ansi.h>
inherit NPC;

mixed random_msg()
{
	if( random(5)==1 )
		QUEST_D->random_emote(this_object(),0,0);
	else	message_vision("$N朝你讨好的说道：如果有拜火教的秘籍残片，可以找俺兑换(huan)。\n",this_object());
	return 1;
}
 
void create()
{
	set_name("书商",({"shu shang","shang"}));
	set_level(35);
	set("per",20);
	set("long","一个目光阴"+({"鹫","冷","森"})[random(3)]+"的汉子，长得短小精悍，黝黑的面上现在堆满讨好的笑容。\n");
        set("gender","男性");
        set("title",HIY"改邪归正的"NOR);
 	set("chat_chance",10);
        set("chat_msg", ({
        	(: random_msg :),
        }));
        set("vendor_goods",1);	
        setup();
        carry_object(0,"cloth",1)->wear();
}

void die()
{
       	message_vision (HIR"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());          
	destruct(this_object());
        return;
}

void unconcious()
{
        die();
}

void kill_ob(object who)
{
	all_inventory(environment())->remove_killer(this_object());
	this_object()->remove_all_killer();
	message_vision("$N讨好的朝$n说道：小的怎么可能是您的对手啊？\n",this_object(),who);
	return;
}

int accept_fight(object who){return 0;}

void init()
{
	add_action("do_list","list");
	add_action("do_huan","huan");
}

int do_list()
{
	string str,type;
	if( !stringp(type=query("type")) )
		return 0;
	str = "你在这里可以兑换的有：\n";	
	switch(type)
	{
		case "spear" : 
			str+= @LONG
	圣火枪法精要 <50级>(spear1)	: 10张枪法碎片
	圣火枪法精要<100级>(spear2)	: 3本圣火枪法精要  <50级>
	圣火枪法精要<120级>(spear3)	: 3本圣火枪法精要 <100级>			
	圣火枪法精要<150级>(spear4)	: 2本圣火枪法精要 <120级>
LONG;
			break;
		case "blade" :
			str+= @LONG
	五虎断门刀精要 <50级>(blade1)	: 10张刀法碎片
	五虎断门刀精要<100级>(blade2)	: 3本五虎断门刀精要  <50级>
	五虎断门刀精要<120级>(blade3)	: 3本五虎断门刀精要 <100级>			
	五虎断门刀精要<150级>(blade4)	: 2本五虎断门刀精要 <120级>
LONG;
			break;
		case "unarmed" :
			str+= @LONG
	五毒神掌精要 <50级>(unarmed1)	: 10张掌法碎片
	五毒神掌精要<100级>(unarmed2)	: 3本五毒神掌精要  <50级>
	五毒神掌精要<120级>(unarmed3)	: 3本五毒神掌精要 <100级>			
	五毒神掌精要<150级>(unarmed4)	: 2本五毒神掌精要 <120级>
LONG;
			break;
		case "sword" :
			str+= @LONG
	烈焰剑法精要 <50级>(sword1)	: 10张剑法碎片
	烈焰剑法精要<100级>(sword2)	: 3本烈焰剑法精要  <50级>
	烈焰剑法精要<120级>(sword3)	: 3本烈焰剑法精要 <100级>			
	烈焰剑法精要<150级>(sword4)	: 2本烈焰剑法精要 <120级>
LONG;
			break;
		case "dodge" :
			str+= @LONG
	离火身法精要 <50级>(dodge1)	: 10张身法碎片
	离火身法精要<100级>(dodge2)	: 3本离火身法精要  <50级>
	离火身法精要<120级>(dodge3)	: 3本离火身法精要 <100级>			
	离火身法精要<150级>(dodge4)	: 2本离火身法精要 <120级>
LONG;
			break;
		default : return 0;
	}
	write(str);
	return 1;
}

int check_inv(object me,string file,int num)
{
	int i;
	object *inv;
	if( !me || !living(me) || me->is_fighting() )
		return 0;
	inv = all_inventory(me);
	if( !inv || !arrayp(inv) || sizeof(inv)<1 )
		return 0;
	for(i=0;i<sizeof(inv);i++)
	{
		if( base_name(inv[i])==file )
		{
			if( inv[i]->query_amount()<num )
				return 0;
			else	return 1;
		}	
	}
	return 0;			
}

int player_payobj(object me,string file,int num)
{
	int i;
	object *inv;
	if( !me || !living(me) || me->is_fighting() )
		return 0;
	inv = all_inventory(me);
	if( !inv || !arrayp(inv) || sizeof(inv)<1 )
		return 0;
	for(i=0;i<sizeof(inv);i++)
	{
		if( base_name(inv[i])==file )
		{
			if( inv[i]->query_amount()>1 )
			{
				if( inv[i]->query_amount()>num )
					inv[i]->add_amount(-num);
				else	destruct(inv[i]);
				return 1;	
			}
			else	return 0;
		}	
	}
	return 0;			
}

int do_huan(string arg)
{
	object obj,me = this_player();
	int n,need_n;
	string str,type,file,need_file;
	if( !stringp(type=query("type")) )
		return 0;
	if( !arg || sscanf(arg,"%s%d",arg,n)!=2 )
		return 0;
	if( n<1 || n>4 )
		return err_msg("没有这本秘籍。\n");
	if( arg!=type )
		return err_msg("我这里只有"+type+"类的秘籍可以兑换。\n");
	file = sprintf("/d/maze/dayan-ta/book/%s_%d",type,n);
	need_file = sprintf("/d/maze/dayan-ta/book/%s_%d",type,n-1);
	switch(n)
	{
		case 1 : need_n = 10;break;
		case 2 : need_n = 3;break;
		case 3 : need_n = 3;break;
		case 4 : need_n = 2;break;
		default: return err_msg("没有这本秘籍。\n");
	}
	if( !check_inv(me,need_file,need_n) )
		return err_msg("你材料不够，没法兑换。\n");
	obj = new(file);
	if( obj->move(me) )
	{
		if( player_payobj(me,need_file,need_n) )
		{
			write("你从"+name()+"处兑换了一本"+obj->name()+"。\n");
			log_file("public",XYJTIME_D->chinese_time(time())+" "+me->query("id")+" get "+file+" by "+need_n+" "+need_file+"\n");
			return 1;
		}
		else
		{
			write("兑换失败！\n");
			if( obj )
				destruct(obj);
			return 1;
		}
	}
	else
	{
		write("兑换失败！\n");
		if( obj )
			destruct(obj);
		write(HIR"【系统】你的包裹满了！"NOR"\n");
		return 1;		
	}		
}