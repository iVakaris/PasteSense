/*#include "hooks/hooks.hpp"
#include "Resolver2.h"
#include "cheats\ragebot\aim.h"
#include "cheats\lagcompensation\animation_system.h"
#include "cheats\lagcompensation\local_animations.h"


std::string ResolverMode[65];
int last_ticks[65];
int IBasePlayer::GetChokedPackets() {
    auto ticks = TIME_TO_TICKS(GetSimulationTime() - GetOldSimulationTime());
    if (ticks == 0 && last_ticks[GetIndex()] > 0) {
        return last_ticks[GetIndex()] - 1;
    }
    else {
        last_ticks[GetIndex()] = ticks;
        return ticks;
    }
}

float CResolver::GetBackwardYaw(IBasePlayer* player) {
    return Math::CalculateAngle(csgo->local->GetOrigin(), player->GetOrigin()).y;
}

float AngleDiff(float destAngle, float srcAngle)
{
    float delta;

    delta = fmodf(destAngle - srcAngle, 360.0f);
    if (destAngle > srcAngle)
    {
        if (delta >= 180)
            delta -= 360;
    }
    else
    {
        if (delta <= -180)
            delta += 360;
    }
    return delta;
}

bool IsAdjustingBalance(IBasePlayer* player, res_record& record, CAnimationLayer layer_2)
{
    for (int i = 0; i < record.m_iLayerCount; i++)
    {
        const int activity = player->GetSequenceActivity(record.animationLayer[i].m_nSequence);
        if (activity == 979)
        {
            layer_2 = record.animationLayer[i];
            return true;
        }
    }
    return false;
}

bool is_breaking_lby(IBasePlayer* player, res_record& cur_record, res_record& prev_record, CAnimationLayer cur_layer, CAnimationLayer prev_layer)
{
    if (IsAdjustingBalance(player, cur_record, cur_layer))
    {
        if (IsAdjustingBalance(player, prev_record, prev_layer))
        {
            if ((prev_layer.m_flCycle != cur_layer.m_flCycle) || cur_layer.m_flWeight == 1.f)
            {
                return true;
            }
            else if (cur_layer.m_flWeight == 0.f && (prev_layer.m_flCycle > 0.92f && cur_layer.m_flCycle > 0.92f))
            {
                return true;
            }
        }
        return false;
    }

    return false;
}

void CResolver::DetectSide(IBasePlayer* player, int* side)
{
    if (!csgo->local || !csgo->local->isAlive() || !csgo->local->GetWeapon())
        return;

    Vector src3D, dst3D, forward, right, up, src, dst;
    float back_two, right_two, left_two;
    trace_t tr;
    Ray_t ray, ray2, ray3, ray4, ray5;
    CTraceFilter filter;

    Math::AngleVectors(Vector(0, GetBackwardYaw(player), 0), &forward, &right, &up);

    filter.pSkip = player;
    src3D = player->GetEyePosition();
    dst3D = src3D + (forward * 384);

    ray.Init(src3D, dst3D);
    interfaces.trace->TraceRay(ray, MASK_SHOT, &filter, &tr);
    back_two = (tr.endpos - tr.startpos).Length();

    ray2.Init(src3D + right * 35, dst3D + right * 35);
    interfaces.trace->TraceRay(ray2, MASK_SHOT, &filter, &tr);
    right_two = (tr.endpos - tr.startpos).Length();

    ray3.Init(src3D - right * 35, dst3D - right * 35);
    interfaces.trace->TraceRay(ray3, MASK_SHOT, &filter, &tr);
    left_two = (tr.endpos - tr.startpos).Length();

    if (left_two > right_two) {
        *side = 1;
    }
    else if (right_two > left_two) {
        *side = -1;
    }
    else
        *side = 1;
}

bool CResolver::DoesHaveJitter(IBasePlayer* player, int* new_side) {
    static float LastAngle[64];
    static int LastBrute[64];
    static bool Switch[64];
    static float LastUpdateTime[64];

    int i = player->GetIndex();

    float CurrentAngle = player->GetEyeAngles().y;
    if (!Math::IsNearEqual(CurrentAngle, LastAngle[i], 50.f)) {
        Switch[i] = !Switch[i];
        LastAngle[i] = CurrentAngle;
        *new_side = Switch[i] ? 1 : -1;
        LastBrute[i] = *new_side;
        LastUpdateTime[i] = interfaces.global_vars->curtime;
        return true;
    }
    else {
        if (fabsf(LastUpdateTime[i] - interfaces.global_vars->curtime >= TICKS_TO_TIME(17))
            || player->GetSimulationTime() != player->GetOldSimulationTime()) {
            LastAngle[i] = CurrentAngle;
        }
        *new_side = LastBrute[i];
    }
    return false;
}

void AntiFreestand(IBasePlayer* player, int* fside)
{
    if (!csgo->local || !csgo->local->isAlive() || !csgo->local->GetWeapon() || !csgo->local->GetWeapon()->GetCSWpnData())
        return;

    bool Autowalled = false, HitSide1 = false, HitSide2 = false;
    auto idx = player->GetIndex();
    float angToLocal = Math::CalculateAngle(interfaces.ent_list->GetClientEntity(interfaces.engine->GetLocalPlayer())->GetOrigin(), player->GetOrigin()).y;
    Vector ViewPoint = interfaces.ent_list->GetClientEntity(interfaces.engine->GetLocalPlayer())->GetOrigin() + Vector(0, 0, 90);
    Vector2D Side1 = { (45 * sin(DEG2RAD(angToLocal))),(45 * cos(DEG2RAD(angToLocal))) };
    Vector2D Side2 = { (45 * sin(DEG2RAD(angToLocal + 180))) ,(45 * cos(DEG2RAD(angToLocal + 180))) };

    Vector2D Side3 = { (50 * sin(DEG2RAD(angToLocal))),(50 * cos(DEG2RAD(angToLocal))) };
    Vector2D Side4 = { (50 * sin(DEG2RAD(angToLocal + 180))) ,(50 * cos(DEG2RAD(angToLocal + 180))) };

    Vector Origin = player->GetOrigin();

    Vector2D OriginLeftRight[] = { Vector2D(Side1.x, Side1.y), Vector2D(Side2.x, Side2.y) };

    Vector2D OriginLeftRightLocal[] = { Vector2D(Side3.x, Side3.y), Vector2D(Side4.x, Side4.y) };

    for (int side = 0; side < 2; side++)
    {
        Vector OriginAutowall = { Origin.x + OriginLeftRight[side].x,  Origin.y - OriginLeftRight[side].y , Origin.z + 90 };
        Vector ViewPointAutowall = { ViewPoint.x + OriginLeftRightLocal[side].x,  ViewPoint.y - OriginLeftRightLocal[side].y , ViewPoint.z };

        if (g_AutoWall.CanHitFloatingPoint(OriginAutowall, ViewPoint))
        {
            if (side == 0)
            {
                HitSide1 = true;
                *fside = 1;
            }
            else if (side == 1)
            {
                HitSide2 = true;
                *fside = -1;
            }

            Autowalled = true;
        }
        else
        {
            for (int sidealternative = 0; sidealternative < 2; sidealternative++)
            {
                Vector ViewPointAutowallalternative = { Origin.x + OriginLeftRight[sidealternative].x,  Origin.y - OriginLeftRight[sidealternative].y , Origin.z + 90 };

                if (g_AutoWall.CanHitFloatingPoint(ViewPointAutowallalternative, ViewPointAutowall))
                {
                    if (sidealternative == 0)
                    {
                        HitSide1 = true;
                        *fside = 1;
                    }
                    else if (sidealternative == 1)
                    {
                        HitSide2 = true;
                        *fside = -1;
                    }

                    Autowalled = true;
                }
            }
        }
    }
    if (!Autowalled)
        resolver->DetectSide(player, fside);
}

void CResolver::Do(IBasePlayer* player, animation* record) {
    auto animstate = player->GetPlayerAnimState();
    if (!animstate)
        return;

    int idx = player->GetIndex();

    if (!vars.ragebot.resolver
        || !csgo->local->isAlive()
        || player->GetPlayerInfo().fakeplayer)

    {
        resolved[idx] = false;
        return;
    }

    CAnimationLayer cur_layer = *player->GetAnimOverlay(1), prev_layer = *player->GetAnimOverlay(1);
    res_record cur_record;
    cur_record.save(player);


    if (Ragebot::Get().target_anims && !csgo->missedshots[idx] &&
        Ragebot::Get().target_anims->player == player && player->GetWeapon() && !player->GetWeapon()->IsMiscWeapon() &&
        Ragebot::Get().target_anims->didshot && fabs(player->GetEyeAngles().x) < 55)
    {
        resolved[idx] = false;
        ResolverMode[idx] = "None[S]";
        return;
    }

    if (vars.ragebot.skip_low_delta && player->GetVelocity().Length2D() > 200 && !csgo->missedshots[idx])
    {
        ResolverMode[idx] = "Skip";
        return;
    }


    if (!is_breaking_lby(player, cur_record, prev_record[idx], cur_layer, prev_layer) && csgo->missedshots[idx] == 0)
    {
        if (player->GetChokedPackets() <= 2 && fabs(player->GetEyeAngles().x) < 55)
        {
            resolved[idx] = false;
            ResolverMode[idx] = "None";
            return;
        }
    }

    float angle = player->GetEyeAngles().y;
    float desync_amount = player->GetDSYDelta() * 0.87f;
    auto full = player->GetAnimOverlays()[3].m_flWeight == 0.0f && player->GetAnimOverlays()[3].m_flCycle == 0.0f;

    static float last_anim_update[64];

    if (csgo->missedshots[idx] == 0 || FreestandSide[idx] == 0)
    {
        if (player->GetVelocity().Length2D() <= 0.1f && full && player->GetAnimOverlays()[6].m_flWeight == 0.0f)
        {
            FreestandSide[idx] = 2 * (AngleDiff(player->EyeAngles()->y, animstate->AbsYaw()) <= 0.0f) - 1;
            last_anim_update[idx] = interfaces.global_vars->realtime;
            desync_amount = 58.f;
        }
        else if (last_anim_update[idx] + 2.f < interfaces.global_vars->realtime || FreestandSide[idx] == 0)
            AntiFreestand(player, &FreestandSide[idx]);
    }

    switch (csgo->missedshots[idx] % 5) {
    case 4:
        ResolverMode[idx] = "brute 4";
        animstate->m_flGoalFeetYaw = angle + (desync_amount * 0.7f) * FreestandSide[idx];

        add_to[idx] = FreestandSide[idx] > 0;
        break;
    case 3:
        ResolverMode[idx] = "brute 3";
        animstate->m_flGoalFeetYaw = angle - (desync_amount * 0.7f) * FreestandSide[idx];

        add_to[idx] = FreestandSide[idx] < 0;
        break;
    case 2:
        ResolverMode[idx] = "brute low";
        animstate->m_flGoalFeetYaw = angle + (desync_amount * 0.18f) * FreestandSide[idx];

        add_to[idx] = FreestandSide[idx] > 0;
        break;
    case 1:
        ResolverMode[idx] = "brute 1";
        animstate->m_flGoalFeetYaw = angle - desync_amount * FreestandSide[idx];

        add_to[idx] = FreestandSide[idx] < 0;
        break;
    case 0:
        ResolverMode[idx] = "brute 0";
        animstate->m_flGoalFeetYaw = angle + desync_amount * FreestandSide[idx];

        add_to[idx] = FreestandSide[idx] > 0;
        break;
    }
    animstate->m_flGoalFeetYaw = Math::NormalizeYaw(animstate->m_flGoalFeetYaw);

    resolved[idx] = FreestandSide[idx] != 0;

    prev_record[idx].save(player);
}
*/