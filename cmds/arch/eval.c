// eval.c
// written by mon 4/21/98

inherit F_CLEAN_UP;

int main(object me, string str)
{
     int start=eval_cost();
     int end;
        int force, mana;
	object ob;
     seteuid(getuid());
     if(str) this_player()->force_me(str);
     end=eval_cost();
     
     write("\nEvaluation Cost: "+(start-end)+" ("+start+" -> "+end+")\n");

     return 1;
}

int help(object me)
{
write(@HELP
指令格式 : eval <command>

This command will return the evaluation cost for <command>.

HELP
    );
    return 1;
}
