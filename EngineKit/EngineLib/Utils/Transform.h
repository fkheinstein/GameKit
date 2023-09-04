#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__



namespace fts
{
    using Vector2f = glm::vec2;
    using Vector3f = glm::vec3;
    using Vector4f = glm::vec4;

    using Matrix4f = glm::mat4;
    using Matrix3f = glm::mat3;
    using Quaternion = glm::quat;

class  Transform {
   public:
    Transform();
    virtual ~Transform() = default;

    void SetPosition(const Vector3f& position);
    void SetRotation(const Quaternion& rotation);
    void SetScale(const Vector3f& scale);
    void SetTransform(const Matrix4f& transform);

    Vector3f GetPosition() const;
    Quaternion GetRotation() const;
    Vector3f GetScale() const;
    Matrix4f GetMatrix() const;

    Vector3f GetRight() const;
    Vector3f GetUp() const;
    Vector3f GetFront() const;

    Vector3f WorldToLocal(const Vector3f& world) const;
    Vector3f LocalToWorld(const Vector3f& local) const;
    Vector3f WorldToLocalVector(const Vector3f& world_vec) const;
    Vector3f LocalToWorldVector(const Vector3f& local_vec) const;


   private:
    Vector3f m_position;
    Quaternion m_rotation;
    Vector3f m_scale;
};


} // namespace fts



#endif // __TRANSFORM_H__