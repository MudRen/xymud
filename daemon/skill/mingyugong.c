// Mingyugong.c 明玉神功
// Cracked by 凌惊雪 4-1-2003
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
        return
notify_fail("明玉神功只能向师父学，或是从运用(exert)中增加熟练度。\n");
}
string exert_function_file(string func)
{
        return CLASS_D("baihuagu") + "/mingyugong/" + func;
}

