#include <ansi.h>

string give_reward(object me) 
{
	mapping ar,skill;
	string *skillnames,selected,msg,*tmp;
	int level,k, i,inc=0;

	if( !me || !living(me) )
        	return 0;
	skill=me->query_skills();        	
	if( !skill || !mapp(skill) )
        	return "none";
	skillnames=keys(skill);
	if( !skillnames || !arrayp(skillnames) )
		return "none";
	tmp = ({});	
	for(i=0;i<sizeof(skillnames);i++)
	{
		if( !skillnames[i] )
			continue;
		if( skill[skillnames[i]]<=100 )
			continue;
		tmp+= ({skillnames[i]});
	}
	if( sizeof(tmp)<1 )
		return "none";			
	selected=tmp[random(sizeof(tmp))];
	level=skill[selected];
	if(level<180) 
        	inc=1;
	else if(level<800) 
        	inc=random(2)==0;
	else if(level<1000)
        	inc=random(4)==0;
	else if(level<1100)
		inc=random(6)==0;
	else if(level<1200)
		inc=random(8)==0;
	else    inc=random(20)==0;
	if( inc==1 ) 
        {
               	skill[selected] = level+1;
               	tell_object(me,HIC"你得到了一级"+ to_chinese(selected) + "。\n"NOR);
               	return selected;
        }
	return "none";
}

