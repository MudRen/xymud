//套装兑换
/*
armor|cloth|head|boots|surcoat
百花谷 蜀山派 大雪山 东海龙宫 无底洞 普陀山
*/
#include <ansi.h>

#define BASE_P 8000

string msg = " (初阶)"NOR"\n "HIY"套装组成 "NOR HIC"盔甲、衣服、帽类、鞋类、披风\n "NOR HIY"套装效果"NOR HIG;

mapping Type_p = ([
	"armor"  : 5,
	"cloth"  : 3,
	"head"   : 2,
	"boots"  : 2,
	"surcoat": 3,
]);

string query_statue(string family_name)
{
	if( !family_name )
		return 0;
	switch(family_name)
	{
		case "百花谷" : return NOR REV WHT"花团锦簇"+msg+" 法术伤害反弹百分比+1%\n          内力后限+200\n          凝神效果追加+1%\n          吸气效果追加+1%\n          物理伤害反弹百分比+1%\n          法力后限+200\n";
		case "陷空山无底洞" : return NOR REV WHT"妖气缭绕"+msg+" 气血自动恢复+10\n          精神自动恢复+10\n          法力自动恢复+10\n          内力后限+500\n          内力自动恢复+10\n";
		case "蜀山派" : return NOR REV WHT"卫道除魔"+msg+" 法术攻击+50\n          内力后限+300\n          攻击命中率+1%\n          物理攻击+50\n          气血后限+600\n";
		case "南海普陀山" : return NOR REV WHT"佛光普照"+msg+" 精神后限+800\n          内力后限+600\n          气血后限+800\n          法力后限+800\n";
		case "东海龙宫" : return NOR REV WHT"呼风唤雨"+msg+" 法术伤害反弹百分比+1%\n          气血治疗附加率+3%\n          内力后限+500\n          法术损伤反弹百分比+1%\n          攻击命中率+3%\n";
		case "大雪山"   : return NOR REV WHT"妖师传人"+msg+" 法力自动恢复+10\n          攻击闪避率+2%\n          内力后限+500\n          内力自动恢复+10\n          攻击命中率+2%\n";
		default : return "";
	}
}

int bangding_mod(object me,object obj)
{
	mapping my,his;
	string *prop,*ids,name;
	int i;
	object armor;
	
	if( !me || !obj || !present(obj,me) 
	 || !living(me) || !interactive(me) )
		return 0;
	armor = new("/obj/armor");
	armor->set("armor_type",obj->query("armor_type"));
	
	name = obj->query("name");
	ids = obj->query_my_id();
	armor->set_name(name,ids);
	armor->set("ids",ids);
	armor->set("names",name);
	my = obj->query_entire_dbase();
	his = armor->query_entire_dbase();
	prop = keys(my);
	for(i=0;i<sizeof(prop);i++)
	{
		if( prop[i]=="name" || prop[i]=="id" 
		 || prop[i]=="valid_time" )
			continue;
		armor->set(prop[i],my[prop[i]]);	
	}
	armor->set("owner_id",me->query("id"));
	armor->setup();
	if( armor->move(me) )
	{
		if( !armor->to_save() )
		{
			if( armor )
				destruct(armor);
			return 0;
		}
		destruct(obj);
		destruct(armor);
		return 1;
	}
	else
	{
		if( armor )
			destruct(armor);
		return 0;	
	}
}

void get_input(string arg, object me)
{
	string file,old_color,fam,title,str;
	object obj,npc;
	int now,need,max,old_armor;
	if( !me )
		return;
	if( !objectp(npc=me->query_temp("pending/mod_ask")) 
	 || !environment(me) )
	{
		return;
	}
	if( !stringp(fam=npc->query("family/family_name"))
	 || me->query("family/family_name")!=fam )
	{
		tell_object(me,CYN+npc->name()+CYN"疑惑的看着你。\n"NOR);
		return;
	}
	if( interactive(npc) )
	{
		tell_object(me,CYN+npc->name()+CYN"诚惶诚恐的看着你。\n"NOR);
		return;
	}	
	if( npc->is_fighting() || npc->is_busy() || !living(npc) )
	{
		tell_object(me,"对方现在无法回应你。\n");		
		return;
	}
	max = me->query_level()/3+1;
	if( sizeof(me->query("euqips"))>=max )
	{
		tell_object(me,"你目前的人物等级，只能绑定 "HIR+max+NOR" 个装备。\n");
		return;	
	}		
	if( (me->query("potential")-me->query("learned_points"))<500 )  
	{
		tell_object(me,"你需要消耗500点潜能。\n");
		return;
	}
	now = me->query("faith");
	need = BASE_P*(Type_p[arg]);
	if( now<need )
	{
		tell_object(me, ("/cmds/std/look.c")->armor_type(arg)+"门派套装兑换需要"HIR+need+NOR"点门派贡献。\n");
		return;
	}
	switch(fam)
	{
		case "百花谷" : title = "百花谷";break;
		case "陷空山无底洞" : title = "无底洞";break;
		case "蜀山派" : title = "蜀山派";break;
		case "南海普陀山" : title = "普陀山";break;
		case "东海龙宫" : title = "东海龙宫";break;
		case "大雪山"   : title = "大雪山";break;
		default :
			tell_object(me,CYN+npc->name()+CYN"疑惑的看着你。\n"NOR);
			return;
	}	
	if( !arg )
	{
		tell_object(me,HIY"你要兑换哪个类型套装，按"HIR"Q"HIY"退出选择 (armor,cloth,head,boots,surcoat)"NOR);
		input_to("get_input",me);
		return;
	}
	if( arg[0..0]=="Q" || arg[0..0]=="q" )
	{
		return;
	}	
	if( member_array(arg,keys(Type_p))==-1 )
	{
		tell_object(me,"这种类型的防具不在兑换套装中。\n");
		tell_object(me,HIY"你要兑换哪个类型套装，按"HIR"Q"HIY"退出选择 (armor,cloth,head,boots,surcoat)"NOR);
		input_to("get_input",me);
		return;
	}

	if( arg=="head" )
		file = "kui";
	else if( arg=="boots" )
		file = "shoes";
	else if( arg=="surcoat" )
		file = "pifeng";
	else	file = arg;
	if( !stringp(old_color=npc->query("env/test")) )
		old_color = "NOR";
	if( !intp(old_armor=npc->query_temp("armor_level"))
	 || old_armor<1 )
		old_armor = 1;
	obj = new("/d/obj/narmor/"+file);
	npc->set("env/test","HIR");
	npc->set_temp("armor_level",30);
	if( obj->init_armor(npc) )
	{
		npc->set("env/test",old_color);
		npc->set_temp("armor_level",old_armor);
		obj->set("armor_title",title);
		obj->delete("class");
		obj->delete("female_only");
		obj->set("family_name",fam);
		obj->set("from","【"+fam+npc->query("name")+"处】");
		if( obj->move(me) )
		{
			obj->set("owner_id",me->query("id"));
			str = obj->short();
			sscanf(str,"%s(%*s",str);
			str = HIW+COLOR_D->clean_color(str)+NOR;
			str = COLOR_D->replace_color(str,1);
			if( bangding_mod(me,obj) )
			{
				me->add("faith",-need);
				tell_object(me,HIR"【系统】你失去了"HIY+need+HIR"点门派贡献。"NOR"\n");
				me->save();
				CHANNEL_D->do_channel(npc,"rumor","听说"+me->name(1)+HIM"得到了"+fam+"秘宝"+str+HIM"！"NOR);
				tell_object(me,HIY"【系统】你可以通过"HIR" zhaohuan [ID] "HIY"命令查看或召唤它，"HIR" destruct <ID> "HIY"命令来注销。"NOR"\n");
				return;
			}
			else
			{
				if( obj )
					destruct(obj);
				tell_object(me,CYN+npc->name()+NOR CYN"说道：你的包裹满了。\n"NOR);	
			}
		}
		else
		{
			if( obj ) destruct(obj);
			tell_object(me,CYN+npc->name()+NOR CYN"说道：你的包裹满了。\n"NOR);
			return;
		}
	}
	else
	{
		tell_object(me,HIR"【系统】套装生成失败！请联系当值巫师。\n"NOR);
		return;
	}	
}

mixed ask_mod(object me,object npc)
{
	string fam,str;
	if( !interactive(me) )
		return 0;
	if( !stringp(fam=npc->query("family/family_name"))
	 || me->query("family/family_name")!=fam )
	 	return 0;	
	str = query_statue(fam);
	if( !str || str=="" )
		return 0;		 	
	if( (wizardp(me) && me->query("env/test"))
	 || me->query_level()>=30 )
	{
		if( me->query_temp("pending/mod_ask")
		 && npc==me->query_temp("pending/mod_ask") )
		{	
		 	tell_object(me,HIY"你要兑换哪个类型套装，按"HIR"Q"HIY"退出选择 (armor,cloth,head,boots,surcoat)"NOR);
		 	input_to("get_input",me);
		 	return "望你能早日天下游历。";	
		}
		else
		{
			me->set_temp("pending/mod_ask",npc);
			tell_object(me,npc->name()+"说道：本门派目前可以兑换的套装是：\n"+str+"\n"NOR);
			tell_object(me,HIY"你要兑换哪个类型套装，按"HIR"Q"HIY"退出选择 (armor,cloth,head,boots,surcoat)"NOR);
		 	input_to("get_input",me);
		 	return "望你能早日天下游历。";	
		}
	}
	else	return 0;	 	
}

void get_input2(string arg, object me)
{
	string file,old_color,fam,title,str;
	object obj,npc;
	int now,need,max,old_armor;
	if( !me )
		return;
	if( !objectp(npc=me->query_temp("pending/fabao_ask")) 
	 || !environment(me) )
	{
		return;
	}
	if( !stringp(fam=npc->query("family/family_name"))
	 || me->query("family/family_name")!=fam )
	{
		tell_object(me,CYN+npc->name()+CYN"疑惑的看着你。\n"NOR);
		return;
	}
	if( interactive(npc) )
	{
		tell_object(me,CYN+npc->name()+CYN"诚惶诚恐的看着你。\n"NOR);
		return;
	}	
	if( npc->is_fighting() || npc->is_busy() || !living(npc) )
	{
		tell_object(me,"对方现在无法回应你。\n");		
		return;
	}
	if( (me->query("potential")-me->query("learned_points"))<500 )  
	{
		tell_object(me,"你需要消耗500点潜能。\n");
		return;
	}
	now = me->query("faith");
	need = 300000;
	if( now<need )
	{
		tell_object(me,HIY"门派法宝兑换需要"HIR"300000"HIY"点门派贡献。\n"NOR);
		return;
	}
	if( !arg )
	{
		if( fam=="蜀山派" )
		 	tell_object(me,HIY"你要兑换哪个类型法宝，按"HIR"Q"HIY"退出选择 (1. 飞行  2. 攻击)"NOR);
	 	else	tell_object(me,HIY"你要兑换哪个类型法宝，按"HIR"Q"HIY"退出选择 (1. 飞行)"NOR);
		input_to("get_input2",me);
		return;
	}
	if( arg[0..0]=="Q" || arg[0..0]=="q" )
	{
		return;
	}	
	if( arg[0..0]=="2" )
	{
		if( fam!="蜀山派" )
		{
			tell_object(me,"本派目前只开放飞行类法宝的兑换。\n");
			tell_object(me,HIY"你要兑换哪个类型法宝，按"HIR"Q"HIY"退出选择 (1. 飞行)"NOR);
			input_to("get_input2",me);
			return;
		}
		else	title = "/quest/fabao/fly/shushan/1_sword2.c";
	}
	if( arg[0..0]=="1" )
	{
		switch(fam)
		{
			case "百花谷" 		: title = "/quest/fabao/fly/baihuagu/1_deng.c";break;
			case "陷空山无底洞" 	: title = "/quest/fabao/fly/wudidong/1_ta.c";break;
			case "蜀山派" 		: title = "/quest/fabao/fly/shushan/1_sword.c";break;
			case "南海普陀山" 	: title = "/quest/fabao/fly/putuo/1_chu.c";break;
			case "东海龙宫" 	: title = "/quest/fabao/fly/longgong/1_cha.c";break;
			case "大雪山"   	: title = "/quest/fabao/fly/xueshan/1_fan.c";break;
			default :
				tell_object(me,CYN+npc->name()+CYN"疑惑的看着你。\n"NOR);
				return;
		}	
	}
	if( !title || strlen(title)<4 )
	{
		tell_object(me,CYN+npc->name()+CYN"疑惑的看着你。\n"NOR);
		return;
	}
	
	npc->set_temp("fabao_level",40);
	npc->set_temp("old_env",npc->query("env/test"));
	npc->set("env/test","HIB");
	obj = new(title);
	obj->init_fabao(npc);
	npc->delete_temp("fabao_level");
	npc->set("env/test",npc->query_temp("old_env"));
	npc->delete_temp("old_env");
	if( !obj->move(me) )
	{
		if( obj ) destruct(obj);
		tell_object(me,CYN+npc->name()+NOR CYN"说道：你的包裹满了。\n"NOR);
		return;
	}
	obj->set("owner_id",me->query("id"));
	obj->set("from","【"+npc->name(1)+"】");
	if( obj->to_save() )
	{
		me->add("faith",-300000);
		tell_object(me,HIR"【系统】你失去了"HIY+"300000"+HIR"点门派贡献。"NOR"\n");
		me->save(1);
	}
	else
	{
		tell_object(me,HIR"【系统】"+obj->name()+HIR"绑定失败！\n"NOR);
		if( obj ) destruct(obj);
		return;
	}
}

//法宝
string fabao_statue(string family_name)
{
	if( !family_name )
		return 0;
	switch(family_name)
	{
		case "百花谷" 		: return NOR HIM"百花灯"NOR"\n"HIC"  法宝效果："NOR"飞行法宝、可储存内力15000、法力15000点，装备有附加属性。\n";
		case "陷空山无底洞"	: return NOR HIR"百妖塔"NOR"\n"HIC"  法宝效果："NOR"飞行法宝、可储存内力8000、法力10000点，装备有附加属性。\n";
		case "蜀山派" 		: return NOR HIY"蜀山飞剑"NOR"\n"HIC"  法宝效果："NOR"飞行法宝、可储存内力8000、法力8000点，装备有附加属性。\n"NOR HIY"蜀山御剑"NOR"\n"HIC"法宝效果："NOR"攻击法宝、装备有附加属性。\n";;
		case "南海普陀山" 	: return NOR HIY"降魔杵"NOR"\n"HIC"  法宝效果："NOR"飞行法宝、可储存内力12000、法力16000点，装备有附加属性。\n";
		case "东海龙宫" 	: return NOR HIY"巡海飞叉"NOR"\n"HIC"  法宝效果："NOR"飞行法宝、可储存内力10000、法力10000点，装备有附加属性。\n";
		case "大雪山"   	: return NOR HIB"招妖幡"NOR"\n"HIC"  法宝效果："NOR"飞行法宝、可储存内力15000、法力8000点，装备有附加属性。\n";
		default : return "";
	}
}

mixed ask_fabao(object me,object npc)
{
	string fam,str;
	if( !interactive(me) )
		return 0;
	if( !stringp(fam=npc->query("family/family_name"))
	 || me->query("family/family_name")!=fam )
	 	return 0;	
	str = fabao_statue(fam);
	if( !str || str=="" )
		return 0;		 	
	if( (wizardp(me) && me->query("env/test"))
	 || me->query_level()>=40 )
	{
		if( me->query_temp("pending/fabao_ask")
		 && npc==me->query_temp("pending/fabao_ask") )
		{	
			if( fam=="蜀山派" )
		 		tell_object(me,HIY"你要兑换哪个类型法宝，按"HIR"Q"HIY"退出选择 (1. 飞行  2. 攻击)"NOR);
		 	else	tell_object(me,HIY"你要兑换哪个类型法宝，按"HIR"Q"HIY"退出选择 (1. 飞行)"NOR);
		 	input_to("get_input2",me);
		 	return "当然如果你收集天下奇珍异宝，也可以炼制法宝。";	
		}
		else
		{
			me->set_temp("pending/fabao_ask",npc);
			tell_object(me,npc->name()+"说道：本门派目前可以兑换的法宝是：\n"+str+"\n"NOR);
			if( fam=="蜀山派" )
		 		tell_object(me,HIY"你要兑换哪个类型法宝，按"HIR"Q"HIY"退出选择 (1. 飞行  2. 攻击)"NOR);
		 	else	tell_object(me,HIY"你要兑换哪个类型法宝，按"HIR"Q"HIY"退出选择 (1. 飞行)"NOR);
		 	input_to("get_input2",me);
		 	return "当然如果你收集天下奇珍异宝，也可以炼制法宝。";	
		}
	}
	else	return 0;	 	
}

int mod_change(object me,object obj)
{
	mapping my_data,base_data;
	string *tmp,*base_prop,str,str2;
	int i,k,j;
	mixed type;
	mapping equip_apply_prop  = ("/cmds/std/look.c")->query_euqip_look1();
	mapping equip_apply_prop2 = ("/cmds/std/look.c")->query_euqip_look2();   

	if( !obj )
		return 0;
	if( obj->query("equipped") )
		return 0;
	
	if( !obj->query("base_level") )
		obj->set("base_level",obj->query("level"));
	tell_object(me,HIG"【系统】"+COLOR_D->clean_color(obj->name())+HIG"升级成功！\n"NOR);
	my_data = obj->query("armor_prop");	
	base_data = ("/d/obj/narmor/newcloth.c")->equip_base(obj);
	base_prop = keys(base_data);
		
	tmp = keys(my_data);
	if( tmp && arrayp(tmp) )
	{
		j = sizeof(tmp);
		j = random(j);
		for(i=0;i<j;i++)
		{
			type = tmp[i];
			if( !stringp(type) || member_array(type,base_prop)!=-1 )
				continue;
			if( my_data[type]>100 )
				continue;			
			k = random(2)+random(obj->query("level")/10)/3;
			if( member_array(type,keys(equip_apply_prop2))!=-1 )
				k = k/2;
			if( k>0 )
			{
				my_data[type]+= k;
				
				if( !undefinedp(equip_apply_prop[type]) )
					str = equip_apply_prop[type];
				else if( !undefinedp(equip_apply_prop2[type]) )	
					str = equip_apply_prop2[type];
				else
				{
					str = type;
					if( is_chinese(to_chinese(str)) )
						str = to_chinese(str)+"有效等级";
					else if( sscanf(str,"ad_%s",str2) )
					{
						if( is_chinese(to_chinese(str2)) )
							str = to_chinese(str2)+"技能等级";
					}
				}
				tell_object(me,HIG"【系统】"+COLOR_D->clean_color(obj->name())+HIG"的 "HIY+str+HIG" 增加了"HIR+k+HIG" 点。\n"NOR);	
			}	
		}
	}
	obj->add("level",1);	
	for(i=0;i<sizeof(base_prop);i++)
	{
		k = base_data[base_prop[i]]+obj->query("level")/3;
		k = k/5+random(k/5);
		if( k<1 ) k = 1;
		if( obj->query("skill_type") && obj->query("weapon_prop") )
			obj->add("weapon_prop/"+base_prop[i],k);
		else	obj->add("armor_prop/"+base_prop[i],k);
		
		if( !undefinedp(equip_apply_prop[base_prop[i]]) )
			str = equip_apply_prop[base_prop[i]];
		else if( !undefinedp(equip_apply_prop2[base_prop[i]]) )	
			str = equip_apply_prop2[base_prop[i]];
		else
		{
			str = base_prop[i];
			if( is_chinese(to_chinese(str)) )
				str = to_chinese(str)+"有效等级";
			else if( sscanf(str,"ad_%s",str2) )
			{
				if( is_chinese(to_chinese(str2)) )
					str = to_chinese(str2)+"技能等级";
			}
		}	
		tell_object(me,HIG"【系统】"+COLOR_D->clean_color(obj->name())+HIG"的 "HIY+str+HIG" 增加了 "HIR+k+" 点"HIG"。\n"NOR);
	}
	obj->add("max_level",1);
	return 1;
}

void get_input3(string arg, object me)
{
	string fam,str,old;
	object obj,npc;
	int need,max,lvl;
	if( !me )
		return;
	if( !objectp(npc=me->query_temp("pending/mod_ask")) 
	 || !environment(me) )
	{
		return;
	}
	if( !stringp(fam=npc->query("family/family_name"))
	 || me->query("family/family_name")!=fam )
	{
		tell_object(me,CYN+npc->name()+CYN"疑惑的看着你。\n"NOR);
		return;
	}
	if( interactive(npc) )
	{
		tell_object(me,CYN+npc->name()+CYN"诚惶诚恐的看着你。\n"NOR);
		return;
	}	
	if( npc->is_fighting() || npc->is_busy() || !living(npc) )
	{
		tell_object(me,"对方现在无法回应你。\n");		
		return;
	}
	
	obj = present(arg,me);
	if( !obj || obj->query("family_name")!=fam
	 || obj->query("owner_id")!=me->query("id")
	 || !obj->query("valid_time") 
         || obj->query("from")!= "【"+fam+npc->query("name")+"处】" 
	 || !obj->query("armor_prop") )
	{
		tell_object(me,"你身上没有"+arg+"或者它不是你的绑定防具。\n");
		return;
	}
	if( obj->query("level")>=me->query_level() )
	{
		tell_object(me,CYN+npc->name()+CYN"朝你摇了摇头。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：你还是先提升自身的人物等级吧。"NOR"\n");
		return;
	}
	if( obj->query("level")>=40 )
	{
		tell_object(me,CYN+npc->name()+CYN"朝你摇了摇头。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：你的"+obj->query("name")+NOR CYN"已无提升空间了。\n"NOR);
		return;
	}
	if( obj->query("equipped") )
	{
		tell_object(me,HIC"你得先卸除"+obj->query("name")+NOR HIC"。\n"NOR);
		return;
	}
		 
	max = 5;
	if( obj->query("family_sj")>=max )
	{
		tell_object(me,CYN+npc->name()+CYN"朝你摇了摇头。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：每件本派套装，师门只能替你升级"NOR HIY"5"NOR CYN"次。"NOR"\n");
		return;
	}
	if( (me->query("potential")-me->query("learned_points"))<500 )  
	{
		tell_object(me,"你需要消耗500点潜能。\n");
		return;
	}
	if( me->query("faith")<100000 )
	{
		tell_object(me,"你需要消耗10万点师门贡献。\n");
		return;
	}
	lvl = obj->query("level");
	switch(obj->query("armor_type"))
	{
		case "armor"   : break;	
		case "cloth"   : break;
		case "head"    : break;
		case "surcoat" : break;
		case "boots"   : break;
		default :
			tell_object(me,CYN+npc->name()+CYN"朝你摇了摇头。\n"NOR);
			tell_object(me,CYN+npc->name()+CYN"说道：师门只能替你升级"NOR HIC"师门套装"NOR CYN"。"NOR"\n");
			return;
	}
	
	if( !mod_change(me,obj) )
		return;
	old = obj->query("name");
	obj->add("family_sj",1);
	obj->setup();
	if( obj->save() )
	{
		CHANNEL_D->do_channel(this_object(),"rumor","听说"+me->name(1)+HIM"将"+fam+"秘宝"HIW+old+HIM"升级了！"NOR);
		me->add("faith",-100000);
		tell_object(me,HIR"【系统】你失去了"HIY"100000"HIR"点师门贡献。"NOR"\n");
	}
	else
	{
		tell_object(me,HIR"【系统】套装保存失败！\n"NOR);
		destruct(obj);
	}	
}

mixed ask_mod_level(object me,object npc)
{
	string fam,str;
	if( !interactive(me) )
		return 0;
	if( !stringp(fam=npc->query("family/family_name"))
	 || me->query("family/family_name")!=fam )
	 	return 0;	
	str = query_statue(fam);
	if( !str || str=="" )
		return 0;		 	
	if( (wizardp(me) && me->query("env/test"))
	 || me->query_level()>=30 )
	{
		if( me->query_temp("pending/mod_ask")
		 && npc==me->query_temp("pending/mod_ask") )
		{	
		 	tell_object(me,HIY"你要升级哪个类型套装，按"HIR"Q"HIY"退出，输入要升级套装的id："NOR);
		 	input_to("get_input3",me);
		 	return "法器乃是外像，多多修炼自身方为正途。";	
		}
		else
		{
			me->set_temp("pending/mod_ask",npc);
			tell_object(me,HIY"你要升级哪个类型套装，按"HIR"Q"HIY"退出，输入要升级套装的id："NOR);
		 	input_to("get_input3",me);
		 	return "法器乃是外像，多多修炼自身方为正途。";	
		}
	}
	else	return 0;	 	
}

