// skill.c
#include <ansi.h>
#include <dbase.h>

mapping skills;
mapping learned;
mapping skill_map;
mapping query_skills() { return skills; }
mapping query_learned() { return learned; }

void set_skill(string skill, int val)
{
	if( !find_object(SKILL_D(skill))
  	  && file_size(SKILL_D(skill)+".c")<0 )
		error("F_SKILL: No such skill (" + skill + ")\n");
	if( userp(this_object()) && val>this_object()->query_level()*10 )
		return;	
	if( !mapp(skills) ) 
        	skills = ([ skill: val ]);
	else    skills[skill] = val;
	if( !mapp(learned) ) 
        	learned = ([ skill: 0]);
	else if( undefinedp(learned[skill]) )
        	(int)learned[skill] = 0;
}

int delete_skill(string skill)
{
	if( mapp(skills) ) 
        {
        	map_delete(skills, skill);
        	if( mapp(learned) ) 
                {
                	map_delete(learned, skill);
                	return undefinedp(learned[skill]);
                }
        	return undefinedp(skills[skill]);
        }
	return 0;
}

varargs void map_skill(string skill, string mapped_to)
{
	if( !mapped_to && mapp(skill_map) ) 
        {
        	map_delete(skill_map, skill);
        	return;
        }
	if( !find_object(SKILL_D(skill))
  	 && file_size(SKILL_D(skill)+".c")<0 )
        	error("F_SKILL: No such skill (" + skill + ")\n");
	if( !mapp(skills) || undefinedp(skills[mapped_to]) )
		return;
	if( !mapp(skill_map) ) 
        	skill_map = ([ skill: mapped_to ]);
	else    skill_map[skill] = mapped_to;
}

string query_skill_mapped(string skill)
{
	if( mapp(skill_map) && !undefinedp(skill_map[skill]) )
        	return skill_map[skill];
	return 0;
}

varargs int query_max_mana()
{
	int s;
	s = 0;
	s+= this_object()->query_skill("spells");	
	s = s * 10;
	return s;
}

varargs int query_max_force()
{
	int s;
	s = 0;
	s+= this_object()->query_skill("force");	
	s = s * 10;
	return s;
}

varargs int query_skill(string skill, int raw)
{
	int s; 
	s = 0; 
	if( !raw ) 
        {
        	if( mapp(skills) && !undefinedp(skills[skill]) ) 
                {
	                s+= (skills[skill]+query_temp("apply/ad_"+skill))/2;
        	        if( mapp(skill_map) && !undefinedp(skill_map[skill]) )
                        {
                	        s+= skills[skill_map[skill]];
                        	s+= query_temp("apply/ad_"+skill_map[skill]);
                        }
			s+= query_temp("apply/" + skill);
        		if( s<0 ) s = 0;
        	}
        	else	s = 0;	
        	return s;
        }
	if( mapp(skills) && !undefinedp(skills[skill]) ) 
        {
        	s = skills[skill];
        	if( raw==1 )
        		s+= query_temp("apply/ad_"+skill);
        	if( s<0 ) s = 0;
        	return s;
        }
	return 0;
}

int add_maximum_mana(int amount)
{
	int j=query("maximum_mana");
	j=j+amount;
	if(j>query_max_mana()) 
        	return 0;
	else if(j<0) j=0;
	set("maximum_mana",j);
	set("max_mana",j); // note here j always <= query_max_mana()
                       // so no problem to set max_mana = j.
	set("mana",0);
	return 1;
}

int add_maximum_force(int amount)
{
	int j=query("maximum_force");
	j=j+amount;
	if(j>query_max_force()) return 0;
	else if(j<0) j=0;
	set("maximum_force",j);
	set("max_force",j);
	set("force",0);
	return 1;
}

mapping query_skill_map()
{
	return skill_map;
}

int skill_death_penalty()
{
	string *sk;
	int i;

	if( wizardp(this_object()) || !mapp(skills) ) 
        	return 0;
	sk = keys(skills);
	if( !mapp(learned) )
        for(i = 0; i<sizeof(sk); i++) 
        {
        	skills[sk[i]]--;
                if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
	}
	else 
	{
		for(i = 0; i<sizeof(sk); i++) 
		{
                	if( (int)learned[sk[i]] > (skills[sk[i]]+1)*(skills[sk[i]]+1)/2 )
                        	map_delete(learned, sk[i]);
                	else    
                	{
                        	skills[sk[i]]--;
                        	if( skills[sk[i]]<0 ) 
                        		map_delete(skills, sk[i]);
                        }
                }
	}                
	skill_map = 0;
	return 1;
}

int skill_death_recover()
{
	string *sk;
	int i, amount;
	if( !mapp(skills) ) 
		return 0;
	if( !this_object()->query("death/skill_loss") )
		return 0;
	sk = keys(skills);
	if( !mapp(learned) )  
        {
        	learned = ([]);
        	for(i = 0; i<sizeof(sk); i++) 
                {
                	amount = (skills[sk[i]]+1) * (skills[sk[i]]+1) * 3 / 4;
                	learned += ([ sk[i] : amount ]); 
                }
        }   
	else    
	{
        	for(i = 0; i<sizeof(sk); i++) 
                {
                	if( undefinedp(learned[sk[i]]) )  
                        {
                        	amount = (skills[sk[i]]+1) * (skills[sk[i]]+1) * 3 / 4;
                        	learned += ([ sk[i] : amount ]);
                        }
                	else    skills[sk[i]]++;
                }
        }
        this_object()->delete("death/skill_loss");
	return 1;
}

varargs void improve_skill(string skill, int amount, int weak_mode)
{
	int skill_lvl,lvl,spi,pp;

	if( !find_object(SKILL_D(skill))
 	&&  file_size(SKILL_D(skill)+".c") < 0 )
        	error("F_SKILL: No such skill (" + skill + ")\n");
	if( !weak_mode || !userp(this_object()) ) 
        {
        	if( !mapp(skills) ) skills = ([]);
        	if( undefinedp(skills[skill]) ) skills[skill] = 0;
        }
        lvl = this_object()->query_level();
        lvl*= 10;
        skill_lvl = skills[skill];
	spi = query("spi");
	if( sizeof(learned) > spi )
        	amount /= sizeof(learned) - spi;
	if( skill_lvl > 950 )
        	amount /= 7;
	else if( skill_lvl > 900 )
        	amount /= 6;
	else if( skill_lvl > 850 )
        	amount /= 5;
	else if( skill_lvl > 800 )
        	amount /= 4;
	else if( skill_lvl > 750 )
        	amount /= 3;
	else if( skill_lvl > 700 )
        	amount = amount * 2 / 5;
	else if( skill_lvl > 450 )
        	amount /= 2;
	if( !amount ) amount = 0;
	pp = query_temp("apply/improve_speed");
	if( pp>100 )
        	pp = 100;
	if( pp>0 )
        	amount+= amount*pp/100; 
	if( !mapp(learned) ) 
        	learned = ([ skill : amount ]);
	else (int)learned[skill] += amount;
	if( (!weak_mode || !userp(this_object()))
  	&& learned[skill] >= (skills[skill] + 1) * 10
  	&& skill_lvl<lvl )
        {
        	skills[skill]++;
        	learned[skill] = 0;
        	tell_object(this_object(), HIC "【系统】你的「"HIY + to_chinese(skill) + HIC"」进步了！\n" NOR);
        	SKILL_D(skill)->skill_improved(this_object());
        }
}

