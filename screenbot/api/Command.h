#ifndef API_COMMAND_H_
#define API_COMMAND_H_

#include <string>
#include <memory>
#include <map>

namespace api {

class Bot;

class Command {
private:
public:
    virtual ~Command() { }
    virtual std::string GetPermission() const = 0;
    virtual void Invoke(api::Bot* bot, const std::string& sender, const std::string& args) = 0;
    virtual std::string GetHelp() const { return ""; }
};
typedef std::shared_ptr<Command> CommandPtr;


class CommandHandler {
public:
    virtual ~CommandHandler() { }

    typedef std::map<std::string, api::CommandPtr> Commands;
    typedef Commands::const_iterator const_iterator;

    virtual void AddPermission(const std::string& player, const std::string& permission) = 0;
    virtual bool HasPermission(const std::string& player, api::CommandPtr command) = 0;
    virtual bool RegisterCommand(const std::string& name, CommandPtr command) = 0;
    virtual void UnregisterCommand(const std::string& name) = 0;

    virtual std::size_t GetSize() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
};

} // ns

#endif
