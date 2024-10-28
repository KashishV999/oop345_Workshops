#ifndef SENECA_SPAMFILTERPLUGIN_H 
#define SENECA_SPAMFILTERPLUGIN_H
#include "plugin.h"
#include "message.h"
namespace seneca {
	constexpr size_t CAPACITY_SP = 10u;
	class SpamFilterPlugin: public Plugin
	{
		std::string spam[CAPACITY_SP]{};
		static int m_cnt;
	public:
		SpamFilterPlugin(const char* filename);

		void operator()(Message& msg) override;
		void showStats() const override;

	};
}
#endif

