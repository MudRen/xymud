// setSkill.c
// 25th, March 1997. - SPY

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int i,j,level;
        mapping skill_status;
        object ob;
        string skill,obj;
        string *skills;
        if( sscanf(arg, "%s %d",skill, level)!=2 )
                return notify_fail("setskill <技能>/all <级别数>。\n");
        ob = me;
        if( !wizardp(me) ) return 0;
if( skill!="all" && !is_chinese(skill) )  return notify_fail("没有"+skill+"这样的技能。\n");
 if( level<0 || level>1000 )  return notify_fail("等级在0-1000之间。\n");
        write(WHT"begin setting skills for "NOR + ob->short(1) + WHT"：\n"NOR);
        if( skill == "all" ) {
                if ( !(skill_status = ob->query_skills()) || !sizeof(skill_status) )
                        return notify_fail("这个人没有学会任何技能，不能用 all 这个参数。\n");
                skills  = keys(skill_status);
                j = sizeof(skill_status);
                for(i=0; i<j; i++) {
                        if( level ==0 ) {
                                ob->delete_skill(skills[i]);
                                write("deleting->" + to_chinese(skills[i]) + 
                                        "(" + skills[i] + ")\n");
                        }
                        else {
                                ob->set_skill(skills[i], level);
                                printf("setting-> %-36s%d\n", to_chinese(skills[i]) + 
                                        "(" + skills[i] + ")", level);
                        }
                }
        }
        else {
                if( level ==0 ) {
                        write("deleting->" + to_chinese(skills[i]) + "(" + skills[i] + ")\n");
                        ob->delete_skill(skill);
                }
                else    {
                        ob->set_skill(skill, level);
                        printf("setting-> %-36s%d\n", to_chinese(skill) + 
                                "(" + skill + ")", level);
                }
        }
        write(WHT"Done.\n"NOR);
        return 1;
}

