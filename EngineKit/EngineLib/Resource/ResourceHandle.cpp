#include <spch.h>


#include "Resource/ResourceHandle.h"



namespace fts
{
template <typename Resource>
class ResourceHandle {
   public:
    ResourceHandle() = default;

    ResourceHandle(Ref<Resource> res) : m_ptr{std::move(res)} {}

    Resource *Get() const { return m_ptr.get(); }

    operator Resource &() const { return *Get(); }

    Resource &operator*() const { return *Get(); }

    Resource *operator->() const { return m_ptr.get(); }

    operator bool() const { return static_cast<bool>(m_ptr); }

    void SetIdentifier(const ResourceId rid) { m_rid = rid; }

    ResourceId GetIdentifier() const { return m_rid; }

   private:
    ResourceId m_rid;
    Ref<Resource> m_ptr;
};
} // namespace fts


