// spell_d.c.
// mon 12/6/98
//lestat 2001 9重新修正
//修正后综述,法术命中率比较高,毕竟这是法术世界,同时反震几率低,反震伤害小
//命中率取决于自身的道行,法术等级
//伤害则完全看自身法力修为和战斗中的enchant大小
//基本上不太可能溢出,法术等级修为的提升,应该是一个自我完善的过程
//施展法术可能遭受的反震伤害则与自身的法术修为有关,修为越高,伤害越小
//不断的提高道行,提高法术等级,则可以增加实战中法术的命中率

#include <ansi.h>
#include <combat.h>
mapping table=([
        "baguazhou": ({"pansi-dafa"}),
        "buddhism": ({"pingtian-dafa"}),
        "dao": ({"yaofa"}),
        "taiyi": ({"moonshentong"}),
        "taoism": ({"dengxian-dafa"}),
        "mysticism": ({"yuxu-spells"}),
        "yuxu-spells": ({"taoism"}),
        "dengxian-dafa": ({"dao"}),
        "pingtian-dafa": ({"mysticism"}),
        "pansi-dafa": ({"buddhism"}),
        "yaofa": ({"gouhunshu"}),
        "gouhunshu": ({"taiyi"}),
        "moonshentong": ({"seashentong"}),
        "seashentong": ({"baguazhou"}),
    ]);

int check_wuxing_kx(object who,object target);

/* determine whether two 法术 are 相克制
   if spell1 克制 spell2, then return = 1.
   if spell2 克制 spell1, then return = -1.
   otherwise, return 0.
   */
int skill_xiangke(string spell1, string spell2)
{
int neutral=0;
int result;    
if ( undefinedp(table[spell1]) 
  || undefinedp(table[spell2])) 
        return neutral;
if ( member_array(spell1, table[spell2])>-1 ) 
        result=-1;// spell2 can 克制 spell1.
else if ( member_array(spell2, table[spell1])>-1 )  
        result=1;// spell1 can 克制 spell2.
else    result=neutral;
return result;
}

/* determine whether two players' 法术 are 相克制
   only effective between two players,
   or a NPC against a player,
   can't a player take advantage of a npc.
   if obj1 克制 obj2, then return = 1.
   if obj2 克制 obj1, then return = -1.
   otherwise, return 0.
   */
int check_xiangke(object obj1, object obj2)
{
int neutral=0;
int result;
string skill1, skill2;    

skill1 = obj1->query_skill_mapped("spells");
skill2 = obj2->query_skill_mapped("spells");
if ( !skill1 && !skill2 )
        return 0;
else if ( !skill1 && skill2 )
        return -1;
else if ( skill1 && !skill2 )
        return 1;
// need at least 20 level of special spells.
if ( (int)obj1->query_skill(skill1,1)<20 ) 
        return neutral;
if ( (int)obj2->query_skill(skill2,1)<20 ) 
        return neutral;
result = skill_xiangke(skill1, skill2);
return result;
}

int valid_damage(object me,object target,int damage)
{
	int myexp,hisexp;
	if( !me || !target )
		return damage;
	myexp = COMBAT_D->valid_power(me->query("daoxing"));
	hisexp = COMBAT_D->valid_power(target->query("daoxing"));
	while( random(hisexp)>myexp )
	{
		damage -= damage / 3;
		hisexp/= 5;
	}
	if( damage<1 ) damage = 1;
	return damage;
}

int attacking_cast_success(object attacker, object target, int success_adj)
{
	int ap, dp, success ,dpp;
	int xk; 
	
	ap = attacker->query_skill("spells");
	ap = ( ap*ap/1000*ap  ); //年做单位进行比较判断.道行超过5000年,提高命中.
	ap = ap*(1+attacker->query("daoxing")/5000000);//5000年道行导致ap*11
	ap = ap+attacker->query("daoxing")/1000;
	dp = target->query("daoxing");
	if( !living(target) )
		dp = 0;
	else if( target->is_busy() )
		dp = dp-random(dp/3);		
	success = 0;
	if( success_adj < 20 ) 
		success_adj = 20;
	else if( success_adj > 500 ) 
		success_adj = 500;
	ap = ap*success_adj/100;
	xk = check_xiangke(attacker, target);
	if( xk==1)
    	dp = dp-random(dp/3);		
	else if(xk==-1) 
    	ap = ap-random(ap/3);		
	xk=0;
	xk = check_wuxing_kx(attacker,target);
	if( xk==1)
    	dp = dp-random(dp/3);		
	else if(xk==-1) 
    	ap = ap-random(ap/3);
	if( ap<1 ) ap = 1;
	if( dp<1 ) dp = 1;    			
	dpp = attacker->query_temp("apply/cast_succ");
	if( dpp<0 ) dpp = 0;
	if( dpp>50 ) dpp = 50;
	ap = ap+ap/100*dpp;
	
	dpp = 0;
	dpp = target->query_temp("apply/cast_dodge");
	if( dpp<0 ) dpp = 0;
	if( dpp>50 ) dpp = 50;
	dp = dp+dp/100*dpp;
	
// Add by jingxue   
// 增加法术抵抗率的设置，通过装备有一定几率可以抵抗法术
// Here apply/resist_spells 为法术抗率
//dpp = target->query_temp("apply/resist_spells");
//    if( random(100)< dpp ) success = 0;
//        if( Int_com(ap,dp,100) ) success = 1;
//if( random(100)>dp*75/(dp+ap) )  success = 1;
  if( random(ap+dp)>dp/2 )  success = 1;
	return success;//命中仅仅取决于自己的法术修为和道行修为,武学和道行完全分离.
}

int attacking_cast_damage(object attacker, object target, int damage_adj)
{
int a_fali, d_fali, damage, damage_bonus ,d_damage;
int xk,ss;
if ( damage_adj < 50 ) 
        damage_adj = 50;
else if( damage_adj > 200 ) 
        damage_adj = 200;
a_fali = attacker->query("mana");
if( a_fali>2*attacker->query("max_mana") ) 
        a_fali = 2*attacker->query("max_mana");
d_fali = target->query("mana");
if ( d_fali>2*target->query("max_mana") ) 
        d_fali = 2*target->query("max_mana");
a_fali=a_fali/40+random(attacker->query("eff_sen") / 20);
d_fali=d_fali/40+random(target->query("eff_sen") / 20);
a_fali+=(damage_adj/100)*(attacker->query("mana_factor"));
d_fali+=(damage_adj/100)*random(target->query("mana_factor"));
//减少法力反弹几率的装备
ss = attacker->query_temp("apply/no_cast_redamage");
if ( ss>100 )
        ss = 100;
if ( ss>0 )
        a_fali+= a_fali/100*ss; 
//增加法力反弹几率的装备
ss = target->query_temp("apply/cast_redamage");
if ( ss>100 )
        ss = 100;
if ( ss>0 )
        d_fali+= d_fali/100*ss; 
if( a_fali > d_fali )        //由于高段位以后升级缓慢,伤害必须封顶
        {
        damage=a_fali-d_fali;
        damage+= (damage_adj/100)*(attacker->query("mana_factor"));
        damage = damage*damage_adj/100;
        damage_bonus = (int)attacker->query_skill("spells")/100;
        if(damage_bonus > 3) damage_bonus = 3;
        damage += damage*damage_bonus;
        d_damage = (int)target->query_temp("apply/armor_vs_spells")/40;//Jingxue
        d_damage+= (int)target->query_temp("apply/armor")/5;
        damage -= d_damage;
        if( damage < 50 ) damage = 50;//最小伤害
        //if( damage > 5000 ) damage = 5000;//伤害封顶
        }
else if( d_fali > a_fali ) 
        {   
        if( d_fali > 400 ) d_fali = 400;
        damage = d_fali;//鼓励使用法术,反震伤害封顶
        damage = damage - target->query("mana_factor"); 
        damage = damage*damage_adj/100;
        damage_bonus = (int)attacker->query_skill("spells")/100;
        if(damage_bonus < 1) damage_bonus = 1;
        if(damage_bonus > 10) damage_bonus = 10;
        damage += damage/damage_bonus;//自身修为的高低在这里起到作用
        }
else    damage=a_fali-d_fali;   
damage = valid_damage(attacker,target,damage);     
return damage;
}

//weiqi 981206
//this function can be called when want apply a damage to a victim while allow
//the victim use his/her self-made fabao to defense.
void apply_damage(object winner, object victim, int damage, string damage_type, string msg_hit)
{
	int i, temp, type, damage_qi, damage_shen,adjust,success;
	object *inv;
	mapping ar;
	int def_count = 0;
	string f_msg,*msg_fabao = ({
        "只见$N的$n霞光一闪！\n",
        "只见$N的$n霞光再闪！\n",
        "只见$N的$n霞光又一闪！\n",
        "只见$N的$n霞光再一闪！\n"
	});
	if( victim->query_temp("anti_magic") )
    {
    	adjust=(int)victim->query_temp("anti_magic");
        if( (int)victim->query("mana") < adjust)
        	success=0;
        else
        	success=1;
        if( success )
		{
                victim->add("mana", -adjust);
                damage_qi=damage_qi - adjust/2;
                damage_shen=damage_shen - adjust/2;
                if( damage_qi > 0 || damage_shen > 0 )
                        message_vision(HIW"\n只见$N"HIW"身后幻出千朵白莲，挡住了$n"HIW"的攻势。\n"NOR, victim, winner);
                else    message_vision(HIW"\n只见$N"HIW"身后幻出千朵白莲，将$n"HIW"的攻势尽数化解。\n"NOR, victim, winner);
        }
	}
//假如wuxing winner被victim所克 ,damage减半
	if( check_wuxing_kx(winner,victim)==-1 )  
    	damage/= 2;
	if( damage <= 0 )
		damage = 1;
	if(damage_type == "qi" || damage_type == "kee") 
    {
    	damage_qi = damage;
        damage_shen = 0;
        type = 0;
	}
	else if(damage_type == "shen" || damage_type == "sen") 
    {
        damage_qi = 0;
        damage_shen = damage;
        type = 1;
    }
	else    
	{
        damage_qi = damage;
        damage_shen = damage;
        type = 2;
    }
//check if the victim equipped defense fabao...
	ar = victim->query_temp("armor");
	if( ar && mapp(ar) )
	{
		inv = values(ar);
		if( inv && arrayp(inv) )
		{
			for( i=0; i<sizeof(inv); i++)
    		{
        		if( !inv[i]->query("series_no") || !inv[i]->query("fabao") )
                	continue;//not a equipped fabao.
        		if( (type == 0) || (type == 2) ) //check if can reduce damage_qi.
                {
                	temp = inv[i]->protect_qi(damage_qi);//temp is the damage left after fabao takes effect.
                	if( temp < damage_qi ) //means fabao useful.
                    {
                    	damage_qi = temp;
                    	f_msg = inv[i]->protect_qi_msg(damage_qi);
                    	if( !f_msg || !stringp(f_msg) )
                    		f_msg = msg_fabao[def_count];
                        message_vision(f_msg, victim, inv[i]);
                        def_count++;    
                        if( def_count>3 )
                        	def_count=0;
					}
                }
        		
        		if( (type == 1) || (type == 2) ) //check if can reduce damage_shen.
                {
                	temp = inv[i]->protect_shen(damage_shen);//temp is the damage left after fabao takes effect.
                	if( temp < damage_shen ) //means fabao useful.
					{
                    	damage_shen = temp;
                    	f_msg = inv[i]->protect_shen_msg(damage_qi);
                    	if( !f_msg || !stringp(f_msg) )
                    		f_msg = msg_fabao[def_count];
                        message_vision(msg_fabao[def_count], victim, inv[i]);
                        def_count++;    
                        if( def_count>3 )
                        	def_count=0;
					}
                }
        	}//end of for i=0 loop.
        }
    }	
//finally we can make damage to the victim...
	if( damage_qi > 0 || damage_shen > 0 )
    	message_combatd(msg_hit, winner, victim);        //produce the hit message...
	else
		message_combatd("结果$N的攻击完全被$n的法宝挡住！\n", winner, victim);//the fabao saved the target...
	if( damage_qi > 0 )
    {
    	victim->receive_damage("kee", damage_qi*3/5, winner,TYPE_CAST);
        victim->receive_wound("kee", damage_qi/2, winner,TYPE_CAST);  
        COMBAT_D->report_status(victim);    
	}
	if( damage_shen > 0 )
    {
        victim->receive_damage("sen", damage_shen*3/5, winner,TYPE_CAST);
        victim->receive_wound("sen", damage_shen/2, winner,TYPE_CAST);    
        COMBAT_D->report_sen_status(victim);
    }
	return;
}

void attacking_cast(
    object attacker, 
    object target, 
    int success_adj, 
    int damage_adj, //default value is 100 for this 2 parameters.
    string damage_type, //must be "shen"/"sen", "qi"/"kee" or "both"(default)
    string msg_init, 
    string msg_success, 
    string msg_fail, 
    string msg_backfire_init,
    string msg_backfire_success)
{
int damage;
message_vision( msg_init, attacker, target );
    
if ( attacking_cast_success(attacker, target, success_adj) == 0 )
        {
        message_combatd( msg_fail, attacker, target );
        target->kill_ob(attacker);  
        return;
        }
damage = attacking_cast_damage(attacker, target, damage_adj);
if ( damage > 0 ) //attacker hit target
        apply_damage(attacker, target, damage, damage_type, msg_success);
else if( damage < 0 ) //backfire
        {
        message_combatd(msg_backfire_init, attacker, target);
        apply_damage(target, attacker, -damage, damage_type, msg_backfire_success);
        }
else //damge=0
        message_combatd(HIB "结果正好被$N以法力逼住，谁也没有吃亏。\n" NOR, target);
target->kill_ob(attacker);
return;
}

//1克制，-1被克，0无，2相生
varargs int wuxing_xs(string wx1,string wx2)
{
	string *wxs = ({"金","木","水","火","土",});
	mapping xsh,wuxing = ([
		"木" : "土", "土" : "水", "水" : "火","火" : "金", "金" : "木",
	]);
	xsh = ([
		"金" : "水", "水" : "木", "木" : "火","火" : "土", "土" : "金",
	]);
	if( !wx1 || !wx2 
	 || member_array(wx1,wxs)==-1
	 || member_array(wx2,wxs)==-1 )
		return 0;
	if( xsh[wx1]==wx2 )
		return 2;	
	else if( wuxing[wx1]==wx2 )
		return 1;
	else if( wuxing[wx2]==wx1 )
		return -1;
	else	return 0;
}		

string query_time_wuxing()
{
	string shi,*sym_dee = ({ "子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥" });	
	int t = ((time()-900000000)*60);
	mixed *local = localtime(t);
	shi = sym_dee[(local[2]%24)/2];
	switch(shi)
	{
		case "子" : return "水";
		case "丑" : return "土";
		case "寅" : return "木";
		case "卯" : return "木";
		case "辰" : return "土";
		case "巳" : return "火";
		case "午" : return "火";
		case "未" : return "土";
		case "申" : return "金";
		case "酉" : return "金";
		case "戌" : return "土";
		case "亥" : return "水";
		default   : return 0;
	}
}

int check_wuxing_kx(object who,object target)
{
	string wx1,wx2;
	if( !who || !target )
		return 0;
	wx1 = FAMILY_D->family_wuxing(who);
	if( !wx1 )
		wx1 = query_time_wuxing();
	else	wx1 = COLOR_D->replace_color(wx1);
	
	wx2 = FAMILY_D->family_wuxing(target);				
	if( !wx2 )
		wx2 = query_time_wuxing();
	else	wx2 = COLOR_D->replace_color(wx2);
	return wuxing_xs(wx1,wx2);
}
