/*
新武器思路V2.0
    Created By Snowtu@tsrj 
*/
#include <ansi.h>
#include <weapon.h>
#include <combat.h>
#include <dbase.h>
inherit EQUIP; 
inherit F_SAVE;

string query_name(){return "特殊武器(+激发)";}

string query_save_file()
{
	string name;
	if( !query("owner_id") || !stringp(query("owner_id")) )
        	return 0;
        name = this_object()->name();
        if( !name || !stringp(name) )
        	return 0;
        name = COLOR_D->clean_color(name);
    	return sprintf("/data/equip/%c/%s/%s_%d_%s", query("owner_id")[0],query("owner_id"),query("skill_type"),query("valid_time"),name);
}

void leave()
{
	remove_call_out("leave");
	write("\n"+this_object()->name()+HIY"化作一道金光冲天而去。\n\n"NOR);
	destruct(this_object());
}

void _leave()
{
	call_out("leave",2+random(5));
}               

void check_owner()
{
	object env = environment();
	if( env )
	{
	    	if( !userp(env) )
                	_leave();
            	if( query("owner_id") && query("owner_id")!=env->query("id") )
                	_leave();                       
	}         
}

int err_msgs(string arg)
{
	write(arg);
    	return 0;
}

int to_save()
{
	int t;
	string type,name;
	mixed *ar;
	object me = environment();
	if( !me || !query("owner_id") 
	 || me->query("id")!=query("owner_id") || query("no_save") )
		return 0;
	if( me->is_busy() )
		return err_msgs("你正忙着。\n");
	if( !type=query("skill_type") )
		return 0;		
	if( query("equipped") )
		return err_msgs("你必须先将"+this_object()->query("name")+"卸下。\n");
	if( (me->query("potential")-me->query("learned_points"))<500 )   
		return err_msgs("你的潜能不够,无法保存法宝。\n");
	me->start_busy(1); 		
	t = time();
	set("valid_time",t);
	ar = me->query("euqips");
	if( !ar || !arrayp(ar) || sizeof(ar)<1 )
		ar = ({});
	ar-= ({0});	
	if( save() )
	{
		set("no_give",1);
        	me->add("potential",-500);
        	name = this_object()->name();
        	if( !name || !stringp(name) )
        		name = "无名";
        	name = COLOR_D->clean_color(name);
        	ar+= ({type+"_"+t+"_"+name});
		me->set("euqips",ar);
		me->save(1);
		tell_object(me,HIY"【系统】"+this_object()->name()+HIY"绑定成功，如果消失，你可以通过 zhaohuan 命令来重新获得。"NOR"\n");
        	return 1;
	}
	return 0;
}        

int do_dest(string arg)
{
	mixed *ar;
	string type;
	object me = this_player();
	if( !arg || !id(arg) )
        	return 0;
	if( me!=environment() )
        	return 0;  
	if( !query("owner_id") || !query("valid_time") )
        	return 0;
	if( !query("skill_type") )
		return err_msg(name()+"武器类型缺失。\n");
	type = sprintf("%s_%d_%s",query("skill_type"),query("valid_time"),this_object()->name());
	type = COLOR_D->clean_color(type);
	if( !arrayp(ar=me->query("euqips"))
	 || sizeof(ar)<1 
	 || member_array(type,ar)==-1 )
		return err_msg(name()+"不是你的绑定装备。\n");	 
	if( query("owner_id")
  	 && me->query("id")!=query("owner_id") )
        	return err_msg(name()+"是"+query("owner_id")+"的专属武器。\n");
	if( (me->query("potential")-me->query("learned_points"))<500 )   
        	return err_msg("你的潜能不够,无法注销法宝。\n");
        seteuid(getuid());
        if( !rm(query_save_file()+ __SAVE_EXTENSION__) )
        	return err_msg("注销失败。\n");
	ar-= ({type});
	ar-= ({0});	
	me->add("potential",-500);
	write("注销成功。\n");
	if( sizeof(ar)>0 )
		me->set("euqips",ar);
	else	me->delete("euqips");
	me->save(1);
	message_vision("$N手中的$n轰的一声炸成了碎片。。。。\n",me,this_object());
	destruct(this_object());
	return 1;
}

void init()
{
    	check_owner();
        add_action("do_dest",({"destruct","zhuxiao"}) );
}

int do_move()
{
    	int i,t,tt;
    	object ridee,me=this_player(); 
    	string room,tmp;

    	if( query("weapon_level")<100 || !query("fly") )
        	return 0;
    	if( this_object()!=me->query_temp("weapon") )  
        	return 0;
    	if( query("owner_id")!=me->query("id") )
        	return 0;
    	if( query("weapon_level")<150 )  
        	t = 3;
    	else if( query("weapon_level")<200 )  
        	t = 2;
    	else t = 1;
    	if( time()<me->query_temp("last_weapon_move")+t 
        || ( !wizardp(me) && environment(me)->query("no_move") )
        || ( !wizardp(me) && environment(me)->query("no_magic") ) )
		return notify_fail(name()+"闪了一闪，没有什么反应。 \n"); 

    	if( me->is_fighting() )
        	return notify_fail("你现在正忙着，无法驾驭"+name()+"！\n");
    	if( me->query("mana")<1500 )
        	return notify_fail("你的法力不够，无法驭"+name()+"飞行。\n");
    	ridee = me->ride();
    	if( ridee )
    	{
        	if( !ridee->move("/d/changan/nbridge") )       
        		return notify_fail("你的坐骑现在动弹不得。\n");
    	}
	message("vision",me->name()+"将手中"+name()+"一摆，口中念咒，喝了一声“疾！”"+name()+"仿佛有灵性一般，似一道飞虹般飞弛而出！

        一时狂沙漫天。。。。
        
等你张开眼时,"+me->name()+"的身影已随之消失在漫天风沙之中。\n"NOR,environment(me),me);
    	tell_object(me,"你将"+name()+"一摆，口中念咒，喝了一声“疾！”"+name()+"仿佛有灵性一般，似一道飞虹般飞弛而出！

        一时狂沙漫天。。。。
        
等你张开眼时,你已随之在半空飞驰。\n"NOR);

    	me->set_temp("last_weapon_move",time());
    	room = "/d/changan/nbridge";
    	if( !me->move(room) )
    	{
        	write("你在天上转了半天也不知该往那边飞。。。\n");
        	message_vision("\n$N失望地从云上跳了下来！\n", me);
    	}
    	message_vision("$N的身影突然出现在一阵狂风之中。\n", me);
    	tt = query("weapon_level")*6;
    	if( me->query("mana")<=tt )
	        tt = me->query("mana")-1;
    	me->add("mana",-tt);
    	return 1;
}

void create()
{
	set_name("◆武器",({"wu qi"}));
}

string short()
{
    	string str;
    	str = query("shorts");
    	if( !str || !stringp(str) )
        	str = ::short();    
    	if( !query("equipped") )  
        	return str;
    	if( this_object()==environment()->query_temp("secondary_weapon") ) 
        	return sprintf("%25-s %s",str,"<副手武器>");
    	else    return sprintf("%25-s %s",str,"<主手武器>");
}

int is_zhaohuan(){ return 1; }    

int hit_ob(object me,object target)
{
	object weapon;
    	int i,ap,dp,damage;
    	mapping act;
    	string tmp,str,*limbs,limb,damage_type,*tt;

    	if( !me || !target || !me->is_fighting(target) )
        	return 0;

    	if( i=query("cure")>0 && me->query("max_kee")-me->query("eff_kee")>= i && query("weapon_level")>20 )
    	{
        	message_combatd("\n$N手中"+name()+"闪出一道柔和之光，$P浸沐其中，伤势渐渐恢复了。。。。\n",me,target);
        	me->receive_curing("kee",i);
    	}
    	
    	if( i=query("busy")>0 && !target->is_busy() && random(me->query_spi())>target->query("spi") && random(10)>5 && query("weapon_level")>30 )
    	{
        	message_combatd("\n$N手中"+name()+"划出一道冰棱，$n冷不丁给冰棱带慢了脚步。\n\n",me,target); 
        	if( i>8 )  i = 8;
        	target->start_busy(i);
    	}
    	
    	if( random(query("weapon_level"))<35 )   
        	return 0;

    	tt = query("condition");
    	if( tt && arrayp(tt) && sizeof(tt) && query("weapon_level")>50 
    	 && !query("be_feng") )
    	{
        	i = sizeof(tt);
        	while(i--)
        	{
            		if( tt[i] && file_size("/daemon/condition/"+tt[i]+".c")>0 
             		&& query("weapon_level")>=50 )
                		target->apply_condition(tt[i],query("weapon_level")/3);
        	}
        	if( target->update_condition() )
            		message_combatd("\n$N手中"+name()+"带出一点绿光，$n闪避不及，绿光在他胸前一闪而没！\n\n",me,target);  
    	}
        
    	weapon = me->query_temp("secondary_weapon");
    	if( !weapon || !objectp(weapon) || !mapp(act=weapon->query("actions"))
    	|| !weapon->is_zhaohuan() )
        	return 0;
	tmp = weapon->query("skill_type");
    	if( me->query_skill(tmp,1) )
    	{
        	tmp = me->query_skill_mapped(tmp);
        	if( tmp && stringp(tmp) )
            		act = SKILL_D(tmp)->query_action(me,weapon);
    	}
    	if( !act || !mapp(act) )
        	act = weapon->query("actions");
    	if( !act || !mapp(act) )
        	return 0;
        me->set("actions",act);
	str = "\n$N将"+query("name")+"交于左手，拿起$w对着$n就是一击。\n";
    	return COMBAT_D->do_attack(me,target,weapon,TYPE_QUICK,str);
}

int apply_conditions(string cnd)
{
	string *cnds = query("condition");
    	string *oo = ({});      
    	int i;

    	if( !cnds || !arrayp(cnds) )
        	cnds = ({});
    	i = sizeof(cnds);     
    	while(i--)
        	if( cnds[i] )  
            		oo+= ({cnds[i]});
    	oo+= ({cnd});
    	set("condition",oo);
    	return 1;    
}

int do_feng(string arg)
{
	object ding,ob = this_object();
    	object me = this_player();
    	string type,tmp;

    	if( !arg || !id(arg) )
        	return 0;
    	if( !present(ob,me) )
        	return 0;
    	if( me->is_busy() || me->query("mana")<500 || me->query("sen")<100 )
        	return err_msg("你目前的状态无法封住"+name()+"的毒性。\n");
	if( ob->query("equipped") )
		return err_msg("你得先将"+name()+"卸除。\n");
    	if( ob->query("be_feng") )
    	{
        	ob->delete("be_feng");
        	write("你将"+name()+"的毒性解封了。\n");
    	}
    	else    
    	{
        	ob->set("be_feng",1);
        	write("你将"+name()+"的毒性封起了。\n");
    	}
    	me->add("mana",-500);
    	ob->save();
    	return 1;
}

// 发挥特殊功能
int do_touch(string arg)
{
    	object me = this_player(),item = this_object();
    	string msg;

    	if( !arg || !id(arg) )
        	return 0;
        if( me->query_level()<40 )
        	return 0;
    	if( !present(item,me) 
     	|| item->query("owner_id")!=me->query("id") )
		return 0;
	if( item->query("equipped") )
        	return err_msg("首先你得将"+item->query("name")+"卸除。\n");
    	if( !item->query("authenticate") )
        	return err_msg(item->query("name")+"尚未鉴定，无法安抚。\n");        
	if( me->query("mana")<2000 
     	 || me->query("mana") < me->query_maxmana()
     	 || me->query("force")<2000 
     	 || me->query("force") < me->query_maxforce() )
        	return err_msg(CYN "\n你凝视" + item->name()+CYN "许久，悠悠一声长叹。\n" NOR);

    	me->add("mana",-1000);
	me->add("force",-1000);
	
    	switch (random(3))
    	{
        	case 0: msg = CYN "\n$N" CYN "轻轻一弹$n" CYN "，长吟道：「别来无恙乎？」\n" NOR;break;
        	case 1: msg = CYN "\n$N" CYN "轻轻抚过$n" CYN "，作古风一首，$n" CYN "铃铃作响，似以和之。\n" NOR;break;
        	default:msg = CYN "\n$N" CYN "悠然一声长叹，轻抚$n"CYN "，沉思良久，不禁感慨万千。\n" NOR;break;
    	}
    	item->add("mana",500+random(500));
    	if( item->query("mana")>=item->query("max_mana")*2 )
    	{
        	item->set("mana",item->query("max_mana")*2 );
        	switch (random(3))
        	{
            		case 0: msg += HIM "忽然只见$n" HIM "闪过一道光华，飞跃而起，散作千百流离。\n" NOR;break;
            		case 1: msg += HIM "顿听$n" HIM "一声龙吟，悠悠不绝，直沁入到你的心肺中去。\n" NOR;break;
            		default:msg += HIM "霎时间$n" HIM "光芒四射，如蕴琉璃异彩，逼得你难以目视。\n" NOR;break;
        	}
	}
    	msg = replace_string(msg, "$n", item->name());
    	message_vision(msg, me);
    	item->save();    
    	return 1;
}

int restore()
{
    if( ::restore() )
    {
        set_name(query("name"),query("ids"));
        return 1;
    }
    return 0;
}
/* 镶嵌物品*/
/*
int do_enchase(string arg)
{
    object tessera,me = this_player(),item = this_object();
    int mana;
    mapping *ins;
    mapping data, spe_data;
    string  *apply;
    string id;

    if( !arg || !present(item,me) )
        return 0;
    
    if( sscanf(arg,"%s in %s",arg,id)!=2 )
        return err_msg("命令格式 enchase <魄石id> in <武器id>\n");

    if( !id(id) )
        return 0;
        
    if( item->query("owner_id")!=me->query("id") )
        return err_msg(item->query("name")+"不是你的专属武器，无法镶嵌。\n");
        
    tessera = present(arg,me);
    if( !tessera || !tessera->is_combine_item() )
        return err_msg("你要镶嵌什么？\n");

鉴定，鉴定能
 1. 得知此武器能否镶嵌 最大凹槽数:combine/max_number 已有凹槽数需找NPC去打
 2. 得知此武器的灵力值，镶嵌时镶嵌魄石等级不同消耗灵力不同，当灵力不够时，无法镶嵌
    当灵力不够时，可以通过touch来补充武器的灵力，消耗玩家的内法上限以及部分的武学
 3. 可能会鉴定出特殊属性，几率与玩家的福缘有关

    if( item->query("equipped") )
        return err_msg("首先你得将"+item->query("name")+"卸除。\n");
    if( !item->query("authenticate") )
        return err_msg(item->query("name")+"尚未鉴定，无法镶嵌魄石。\n");        
//有无凹槽
    if( item->query("combine/max_number")<1  //最大凹槽数
     || item->query("combine/open_number")<1 ) //已有凹槽数
        return err_msg(item->query("name")+"上没有凹槽用来镶嵌魄石。\n");

    if( item->query("combine/enchase_number")>=item->query("combine/open_number") 
     || item->query("combine/enchase_number")>=item->query("combine/max_number") )
        return err_msg(item->query("name")+"上已镶嵌不了更多的魄石了。\n");
        
    mana = tessera->query_need_mana();
    if( !mana || mana<0 )
        mana = 100*(item->query("combine/open_number")+1);
    if( mana>item->query("max_mana") )
        return err_msg(item->query("name")+"灵力不足，没有必要镶嵌" + tessera->query("name") + "。\n");        
    if( mana>item->query("mana") )
        return err_msg(item->query("name")+"灵力不足，不能发挥" + tessera->query("name") + "的威力。\n");        
    if( me->is_busy() )
        return err_msg("你现在在正忙着呢。\n");

    me->start_busy(1);        
    message_vision(HIM "“喀啦”一声，$N" HIM "将" + tessera->name() + "镶嵌到了$n" HIM "上面。\n"NOR,me,item);
//镶嵌失败
    if( !tessera->do_enchase(me,item) )       
    {
        message_vision(HIM"结果什么反应都没有。\n"NOR,me);
        tell_object(me,HIC"镶嵌失败了。\n"NOR);
        me->start_busy(2);
        return 1;
    }
    message_vision(HIM"\n只见$n"HIM "上隐隐的显过了一道奇异的光芒，随即变得平静，说不出的平凡。\n\n" NOR, me, item);
    tell_object(me, HIC "你感受" + item->name() + HIC "发生了不可言喻的变化。\n" NOR);
//镶嵌数增加1
    item->add("combine/enchase_number",1);
//灵力消耗
    item->add("mana",-mana);
    item->save();        
    return 1;
}

//伤害加成，在combat_d中调用
int valid_damage(object me,object target)
{
    if( !me || !target || !me->is_fighting(target) )
        return 0;
    return 1;
}
*/    
string name()
{
	string cls,name = ::name();
        if( query("weapon_title") )
                name = query("weapon_title")+"之"+name;
	if( query("weapon_color") )
	{
                name = query("weapon_color")+name;       
		name = COLOR_D->replace_color(name,1);
                if( query("weapon_color")=="HIM" )
		{
			if( query("level")<30 )
				name = HIM"(鬼)"+name;
			else if( !stringp(cls=query("class")) )
				name = HIM"(灵)"+name;
			else
			{
				switch(cls)
				{
					case "shen" : 
					case "dragon" :
					case "fighter" :
					case "xian" : name = HIM"(仙)"+name;break;
					case "youling" :
					case "ghost" : name = HIM"(鬼)"+name;break;
					case "seng"  :
					case "bonze" : name = HIM"(佛)"+name;break;
					case "taoist": name = HIM"(道)"+name;break;
					case "scholar" : name = HIM"(儒)"+name;break;
					case "dancer" : name = HIM"(魅)"+name;break;
					case "yaomo" : name = HIM"(妖)"+name;break;
					case "tianmo" : name = HIM"(魔)"+name;break;
					default : name = HIM"(灵)"+name;break;
				}
			}	
		}
	}
	return name;
}
