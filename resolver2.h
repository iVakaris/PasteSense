/*
#pragma once
struct animation;

struct res_record
{
    int m_iLayerCount;
    CAnimationLayer animationLayer[15];

    void save(IBasePlayer* player)
    {
        m_iLayerCount = player->GetNumAnimOverlays();
        for (int i = 0; i < m_iLayerCount; i++)
            animationLayer[i] = player->GetAnimOverlays()[i];
    }

};

class CResolver
{
private:
    float GetLeftYaw(IBasePlayer*);
    float GetRightYaw(IBasePlayer*);
    bool TargetSide(IBasePlayer*);
    bool TargetJitter(IBasePlayer*, bool);
    bool DoesHaveJitter(IBasePlayer*, int*);
    res_record arr_infos[65];
    res_record prev_record[65];
public:
    float GetAngle(IBasePlayer*);
    float GetForwardYaw(IBasePlayer*);
    float GetBackwardYaw(IBasePlayer*);
    void DetectSide(IBasePlayer*, int*);
    void Do(IBasePlayer*, animation* record);
    bool add_to[64];
    bool resolved[64];
    int FreestandSide[64];
    int JitterSide[64];
};
extern CResolver* resolver;
extern std::string ResolverMode[65];
*/