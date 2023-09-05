#ifndef B7E8FA9A_361F_40F5_AABC_42DAC556D172
#define B7E8FA9A_361F_40F5_AABC_42DAC556D172


#include <cstdint>

namespace fts
{

    class  ResourceId {
    public:
        ResourceId();
        ResourceId(uint64_t resource_id);
        ResourceId(const char* c_str);
        ResourceId(const std::string_view& str);
        ResourceId(const std::string& str);
        ResourceId(const ResourceId&) = default;
        ~ResourceId() = default;

        operator uint64_t() const { return m_resource_id; }

        //SERIALIZE(m_resource_id)

    private:
        uint64_t m_resource_id;
    };

} // namespace fts


namespace std {
    template <>
    struct hash<fts::ResourceId> {
        std::size_t operator()(const fts::ResourceId& resource_id) const
        {
            return hash<uint64_t>()(static_cast<uint64_t>(resource_id));
        }
    };
}  // namespace std

#endif /* B7E8FA9A_361F_40F5_AABC_42DAC556D172 */
