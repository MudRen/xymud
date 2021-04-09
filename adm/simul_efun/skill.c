// skill.c
// Created By Jingxue 2007/06/11 For 幻想群英 The Fantasy of the Hero


// Modified By Jingxue 2007/06/11
/*
原skill目录放置系统本身提供的技能
own_skill目录放置玩家自创的技能
*/

nomask string search_skill(string skill)
{
	if(!stringp(skill) || skill == "")
		return 0;
	if( file_size(SKILL_SYS_D(skill)+".c") > 0 )
		return SKILL_SYS_D(skill);
	else if( file_size(SKILL_SELF_D(skill)+".c") > 0 )
		return SKILL_SELF_D(skill);
		
	return 0;
}

// Modified By Jingxue 2007/06/11
nomask string search_jifa(string skill)
{
	if(!stringp(skill) || skill == "")
		return 0;
	if( file_size(PERFORM_D(skill)+".c") > 0 )
		return PERFORM_D(skill);
	else if( file_size(CAST_D(skill)+".c") > 0 )
		return CAST_D(skill);
	else if( file_size(EXERT_D(skill)+".c") > 0 )
		return EXERT_D(skill);
	else if( file_size(JIFA_SELF_D(skill)+".c") > 0 )
		return JIFA_SELF_D(skill);
		
	return 0;
}

/*
nomask string query_skill_class(string skill)
{
	string t_skill,s_class;

	if( !(t_skill = search_skill(skill)) )
		return 0;

	if(!sscanf(t_skill,"/daemon/skill/%s/"+skill,s_class))
		return 0;

	else
		return s_class;
}
*/