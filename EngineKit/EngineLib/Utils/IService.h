#ifndef __ISERVICE_H__
#define __ISERVICE_H__


namespace fts
{
    class IService
	{
	public:
		IService() = default;
		virtual ~IService() = default;

		virtual void OnCreate() = 0;
		virtual void OnDestroy() = 0;
	};
} // namespace fts

#endif // __ISERVICE_H__