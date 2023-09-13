#ifndef __SCENEBUILDERLAYER_H__
#define __SCENEBUILDERLAYER_H__


#include "Core/Layer.h"


namespace app01
{

    class SceneBuilder : public fts::Layer
    {

    public:
        SceneBuilder();
        ~SceneBuilder();


        virtual void OnPush() override;
        virtual void OnPop() override;

    private:
        void CreateDirLight();
        void CreateEnemyShip();
        void CreateLight();
        void CreateObject();

        void CreateUIObject();

    };


} // namespace app01


#endif // __SCENEBUILDERLAYER_H__