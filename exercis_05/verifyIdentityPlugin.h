#ifndef SENECA_VERIFYIDENTITYPLUGIN_H
#define SENECA_VERIFYIDENTITYPLUGIN_H
#include "plugin.h"
#include "message.h"
namespace seneca {
	constexpr size_t CAPACITY_VIP = 10u;

	class VerifyIdentityPlugin: public Plugin
	{
		std::string trusted[CAPACITY_VIP]{};
		
	public:
		VerifyIdentityPlugin(const char* filename);

		void operator()(Message& msg) override;

		void showStats()const override;

	};
}
#endif

