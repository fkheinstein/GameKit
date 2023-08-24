#ifndef BB81C27E_2A52_43A4_B24A_3102FF664D88
#define BB81C27E_2A52_43A4_B24A_3102FF664D88


#include <Application/IApplication.h>

namespace app01
{
    class SandboxApp : public fts::Application 
    {

    public:
        SandboxApp(/* args */);

        void OnInit() override;
        void OnDestroy() override;

    private:

    };


} // namespace fts

#endif /* BB81C27E_2A52_43A4_B24A_3102FF664D88 */
