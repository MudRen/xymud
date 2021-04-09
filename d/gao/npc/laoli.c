/***************************
	挑战武器升级2
***************************/
#include <ansi.h>
inherit F_VENDOR_SALE;

string check_weapon();

void create()
{
	reload("lao_li");
	set_name("老李头", ({"lao li", "li"}));
	set("long", "铁铺的主人．\n");
	set("gender", "男性");
	set("title", "铁匠");
	set("per", 15);
	set("combat_exp", 6800);
	set("age", 56);
	set("attitude", "friendly");
	set("shen_type", 1);
	set_skill("unarmed", 15);
	set("chat_chance", 5);
	set("chat_msg", ({
		name()+"一脚踢在小学徒的屁股上，嚷道：不许偷懒！\n",
		name()+"对小学徒嚷道：教你多少次了！你怎么这么笨！\n",
		name()+"说道：听说宝象锡器铺的新到了一批高等级的锡。\n",
		name()+"说道：听说西域比丘的金器店里有高纯度的金。\n",
		name()+"大声对着小学徒嚷道：再不学好，把你送去祭赛银器店卖银！\n",
		name()+"说道：听说西域天竺首饰店里有奇珍寒玉卖，真想见识见识哈。\n",
		name()+"喃喃自语：从天竺玉华县的铁匠铺新进的一批铜不知能不能用。\n",
		name()+"说道：本店的天外飞石绝对真货！\n",
		name()+"说道：若论铁矿，还是无底洞铁匠铺的好。\n",
		name()+"说道：西域钦法的寒铁可是炼兵器的好材料。\n",
	}) );
	set("vendor_goods", ([
		"blade": "/d/gao/obj/blade",
		"sword": "/d/gao/obj/sword",
		"dagger": "/obj/example/dagger",
		"yunshi" : "/d/obj/yelian/yunshi",
	]) );
	set("inquiry", ([
	//	"锻造"  : (: check_weapon :),
	]));	 
	setup();
	add_money("coin", 50+random(200));
	carry_object("/obj/cloth")->wear();
	carry_object("/d/obj/weapon/hammer/hammer")->wield();
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

string check_weapon()
{
	object weapon,me = this_player();
	if( me->query_temp("挑战武器_锻造") )
		return "罗罗嗦嗦的做什么！";
	weapon = me->query_temp("weapon");
	if( !weapon )
		return "你手上好似没拿武器哈。";
//普通武器也可锻造，只是下线就米了			
	if( weapon->is_zhaohuan() && weapon->query("weapon_level")<10 )
		return "你的"+weapon->name()+CYN"等级不够，无法锻造。"NOR;
	command("nod "+me->query("id"));
	write(CYN+name()+"说道：既然你想要锻造"+weapon->query("name")+CYN"，老朽就成全了你。\n"NOR);
	write(CYN+name()+"说道：锻造是门高深的技术，你再给小老儿千两黄金，小老儿自当替你锻造。\n"NOR);
	me->set_temp("挑战武器_锻造",weapon);
	return "锻造之技，始自盘古开天地，初成于女娲补天。可是门高深的学问哈。";
}

void weapon_name(object me,object weapon,string arg) 
{
	mapping data;
	int i,type=0;
	string *msg,str,id,name,ndata,long,oldname;
	if( !me )		return;
	if( !weapon )
	{
		write(CYN+name()+"疑惑的说道：咦，你要锻造的武器怎么不见了？！\n"NOR);
		command("bug "+me->query("id"));
		return;
	}		 
	id = weapon->query_temp("yelian_id");	
	oldname = weapon->query("name");
	weapon->unequip();

	if( arg=="1" )
		arg = weapon->name(1);
	else	 
	{		 
		msg = ({"兔","snowtu","靠","操","妈","你娘","日你","日死"});
		if( member_array(arg,msg)!=-1 )
		{
			write("你输入的信息可能含有非法信息，请重新输入。\n");  
			write("请输入重新锻造后武器的名称(4-10个汉字长度，支持颜色)，如果不变，请输入 1 :");
			input_to( (: call_other, __FILE__, "weapon_name",me,weapon:));		  
			return;
		}
		str = COLOR_D->replace_color(arg);
		if( !is_chinese(str) )
		{
			write("你输入的信息必须是中文信息，请重新输入。\n");	 
			write("请输入重新锻造后武器的名称(4-10个汉字长度，支持颜色)，如果不变，请输入 1 :");
			input_to( (: call_other, __FILE__, "weapon_name",me,weapon:));		  
			return;
		}
	}
	arg = COLOR_D->replace_color(arg,1);
	if( weapon->is_zhaohuan() )
		weapon->set_name(arg,({id,weapon->query("skill_type")}));
//更改描叙
	long = weapon->query("long");
	msg = explode(long,"\n");
	long = HIY+me->query("name")+"("+capitalize(me->query("id"))+")亲手锻造的"NOR+arg+NOR+HIY"。\n"NOR;
	for(i=1;i<sizeof(msg);i++)
		long+= msg[i];
	weapon->set("long",long);	
	if( random(50)>(100-me->query("kar")) || wizardp(me) )
	{
		i = random(5);  
		if( i>0 )
		{
			weapon->add("weapon_prop/damage",i);
			write(HIR"你的武器的攻击力提高"+i+"点！\n"NOR);
			type++;
		}
	}

	if( random(50)>(50-me->query("kar")) || wizardp(me) )
	{
		data = weapon->query("weapon_prop");
		msg = keys(data);
		for(i=0;i<sizeof(msg);i++)
		{
			if( data[msg[i]]>=0 )
				continue;
			data[msg[i]] = 1;					 
			write(HIR"你的武器的属性提高了！\n"NOR);
			type++;
		}
	}

	if( random(50)>(50-me->query("kar")/2)  || wizardp(me) )
	{
		ndata = weapon->query("skill_type");
		if( !ndata )  ndata = "parry";
		ndata = ({"dodge","parry","force","spells",ndata,})[random(5)];
		data = weapon->query("weapon_prop");
		if( undefinedp(data[ndata]) ) 
		{
			data[ndata] = 1+random(5);
			write(HIR"你的武器的属性提高了！\n"NOR);
			type++;
		}
	}
	if( weapon->is_zhaohuan() )	
		weapon->save();	
	if( type>0 )
		CHANNEL_D->do_channel(me,"rumor","听说"HIW+me->name(1)+HIM"将"HIG+oldname+HIM"重新锻造为"HIG+weapon->name()+HIM"，质地得到了很好的提高！"NOR);	 
	me->delete_temp("挑战武器_锻造_gived");
	me->delete_temp("挑战武器_锻造");
	me->delete_temp("挑战武器_锻造_obj");
	return;				 
}

void weapon_id(object me,object weapon,string arg) 
{
	if( !me )		return;
	if( !weapon )
	{
		write(CYN+name()+"疑惑的说道：咦，你要锻造的武器怎么不见了？！\n"NOR);
		command("bug "+me->query("id"));
		return;
	}
	if( arg=="1" )
	{
		arg = weapon->query("id");		
		write("你决定武器的ID继续使用 "+arg+"\n");		
		weapon->set_temp("yelian_id",arg);
		write("请输入重新锻造后武器的名称(4-10个汉字长度，支持颜色)，如果不变，请输入 1 :");
		input_to( (: call_other, __FILE__, "weapon_name",me,weapon:)); 
		return;
	}			 
	if( !LOGIN_D->check_legal_id(arg) ) 
	{
		write("请输入重新锻造后武器的ID(3-8个英文字母，如果不变，请输入 1 ) :");
		input_to( (: call_other, __FILE__, "weapon_id",me,weapon:)); 
		return;
	}
	if( weapon->is_zhaohuan() 
	&& me->query("new_item/"+arg) )
	{
		write("你的挑战武器里已经有名为"+arg+"的武器存在了。\n");		 
		write("请输入重新锻造后武器的ID(3-8个英文字母，如果不变，请输入 1 ) :");
		input_to( (: call_other, __FILE__, "weapon_id",me,weapon:)); 
		return;
	}		 
	weapon->set_temp("yelian_id",arg);
	write("请输入重新锻造后武器的名称(4-10个汉字长度，支持颜色)，如果不变，请输入 1 :");
	input_to( (: call_other, __FILE__, "weapon_name",me,weapon:)); 
}

int change_weapon(object me)
{
	object weapon;  
	if( !me )		return 0;
	weapon = me->query_temp("挑战武器_锻造");
	if( !weapon ) 
	{
		write(CYN+name()+"疑惑的说道：咦，你要锻造的武器怎么不见了？！\n"NOR);
		command("bug "+me->query("id"));
		return 0;
	}
	write(CYN+name()+"“啧啧”的咂了几下嘴。\n"NOR);
	write(CYN+name()+"说到：好，既然如此，老朽就替你重新锻造这"+weapon->query("unit")+weapon->name()+CYN"。\n"NOR);
	write("请输入重新锻造后武器的ID(3-8个英文字母，如果不变，请输入 1 ) :");
	input_to( (: call_other, __FILE__, "weapon_id",me,weapon:)); 
	return 1;
}		 

int accept_object(object me,object obj)
{
	int num,k;	
	object stone;	
	if( !me->query_temp("挑战武器_锻造") )
	{
		write(CYN+name()+"疑惑的看着你。\n"NOR);
		return 0;
	}
	if( !me->query_temp("挑战武器_锻造_gived") )
	{
		if( !obj->query("money_id") )
			return 0;
		if( obj->value()<10000000 )	 
		{
			write(CYN+name()+"不耐烦的说：嫌少！嫌少！\n"NOR);
			return 0;
		}
		stone = new("/d/obj/yelian/"+({"hantie","hanyu","jin","tie","tong","xi","yin","yunshi",})[random(8)]);
		if( !stone )				
		{
			command("hmm");
			write(name()+"说道：昨日学徒不甚将炉火熄了，这几天是不能锻造了。\n");
			return 0;
		}
		num = 2+random(4);
		k = 1;
		stone->set("item_level",num);
		command("nod");
		write(name()+"说道：你只需给老朽"+chinese_number(k)+"块"+stone->name()+"，就行了。\n");
		me->set_temp("挑战武器_锻造_gived",1);
		me->set_temp("挑战武器_锻造_obj/name",stone->query_yelian_type());
		me->set_temp("挑战武器_锻造_obj/number",k);
		me->set_temp("挑战武器_锻造_obj/level",num);
		me->set_temp("挑战武器_锻造_obj/short",stone->name());
		if( stone ) 
			destruct(stone);
		return 1;
	}
	else	 
	{
		if( !obj->is_yelian() )
		{
			write(name()+"皱了皱眉头：这可不是冶炼材料。。。。\n");
			return 0;
		}
		if( obj->query_yelian_type()!=me->query_temp("挑战武器_锻造_obj/name") )
		{
			write(name()+"皱了皱眉头：老朽要的是"+me->query_temp("挑战武器_锻造_obj/name")+"。\n");
			return 0;
		}
		if( obj->query("item_level")!=me->query_temp("挑战武器_锻造_obj/level") )
		{
			write(name()+"皱了皱眉头：老朽要的是"+me->query_temp("挑战武器_锻造_obj/short")+"。\n");
			return 0;
		}
		if( obj->query_amount()<me->query_temp("挑战武器_锻造_obj/number") )
		{
			k = me->query_temp("挑战武器_锻造_obj/number")-obj->query_amount();
			write(name()+"皱了皱眉头：尚缺"+chinese_number(k)+"块。\n");
			return 0;
		}
		return change_weapon(me);
	}
} 
