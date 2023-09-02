#ifndef __CASCADESHADOW_H__
#define __CASCADESHADOW_H__



namespace fts
{

    class Camera;
    class Texture;
    class Framebuffer;
    class Transform;

    class CascadeShadow {
    public:
        CascadeShadow();
        void CreateShadowMap(int32_t width = 4096, int32_t height = 4096);
        void DestroyShadowMap();
        const std::vector<glm::mat4>& GetLevelProjectionView() const
        {
            return m_projection_views;
        }

        void SetCascadePlanes(const std::vector<float>& planes)
        {
            m_cascade_planes = planes;
        }

        void SetNumOfCascades(int32_t num_of_cascades);
        const std::vector<float>& GetCascadePlanes() const
        {
            return m_cascade_planes;
        }

        void ComputeCascadeLightMatrix(const Transform& transform,  const Camera& camera);

        Texture* GetShadowMap() const { return m_cascade_map.get(); }
        Framebuffer* GetShadowTarget() const { return m_cascade_fb.get(); }

    private:
        int32_t m_width;
        int32_t m_height;
        Ref<Framebuffer> m_cascade_fb;
        Ref<Texture> m_cascade_map;

        std::vector<glm::mat4> m_projection_views;
        std::vector<float> m_cascade_planes;
    };
} // namespace fts


#endif // __CASCADESHADOW_H__