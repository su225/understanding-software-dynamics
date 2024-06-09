#include <sys/sysctl.h>
#include <iostream>
#include <map>
#include <string>
#include <format>
#include <array>

template<typename T>
inline std::optional<T> get_sysctl_value(std::string sysctl) {
    T val;
    auto data_len = sizeof(val);
    return sysctlbyname(sysctl.c_str(), &val, &data_len, nullptr, 0) == 0
        ? std::optional<T>(val) : std::nullopt;

}

inline decltype(auto) get_perf_level_specific_sysctl_name(auto perf_level = 0, auto suffix = "") {
    return std::format("hw.perflevel{}.{}", perf_level, suffix);
}

typedef struct apple_hardware_perflevel {
    uint64_t perf_level;
    uint64_t cpus_per_l2_cache;
    uint64_t cpus_per_l3_cache;
    uint64_t l1_instruction_cache_size_bytes;
    uint64_t l1_data_cache_size_bytes;
    uint64_t l2_cache_size_bytes;
    uint64_t l3_cache_size_bytes;

    uint64_t cur_enabled_logical_proc_cores;
    uint64_t cur_enabled_physical_proc_cores;
    uint64_t max_enabled_logical_proc_cores;
    uint64_t max_enabled_phyiscal_proc_cores;
}apple_hardware_perflevel;

typedef struct apple_hardware_stats {
public:
    uint64_t cur_enabled_logical_proc_cores;
    uint64_t cur_enabled_physical_proc_cores;
    uint64_t max_enabled_logical_proc_cores;
    uint64_t max_enabled_phyiscal_proc_cores;

    uint64_t cache_line_size_bytes;
    uint64_t dram_size_bytes;
    uint64_t virtual_memory_page_size_bytes;

    uint64_t num_perf_levels;
    std::map<uint8_t, apple_hardware_perflevel> topology;

    apple_hardware_stats();
    void print();
}apple_hardware_stats;

apple_hardware_stats::apple_hardware_stats() {
    this->cur_enabled_logical_proc_cores = get_sysctl_value<uint64_t>("hw.activecpu").value_or(0);
    this->max_enabled_logical_proc_cores = get_sysctl_value<uint64_t>("hw.ncpu").value_or(0);
    this->cur_enabled_physical_proc_cores = get_sysctl_value<uint64_t>("hw.physicalcpu").value_or(0);
    this->max_enabled_phyiscal_proc_cores = get_sysctl_value<uint64_t>("hw.physicalcpu_max").value_or(0);

    this->cache_line_size_bytes = get_sysctl_value<uint64_t>("hw.cachelinesize").value_or(0);
    this->dram_size_bytes = get_sysctl_value<uint64_t>("hw.memsize").value_or(0);
    this->virtual_memory_page_size_bytes = get_sysctl_value<uint64_t>("hw.pagesize").value_or(0);

    this->num_perf_levels = get_sysctl_value<uint64_t>("hw.nperflevels").value_or(0);

    for (uint64_t pl = 0; pl < this->num_perf_levels; pl++) {
        apple_hardware_perflevel pl_stats;
        pl_stats.perf_level = static_cast<uint64_t>(pl);
        pl_stats.cpus_per_l2_cache = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "cpusperl2")).value_or(0);
        pl_stats.cpus_per_l3_cache = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "cpusperl3")).value_or(0);
        pl_stats.l1_instruction_cache_size_bytes = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "l1icachesize")).value_or(0);
        pl_stats.l1_data_cache_size_bytes = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "l1dcachesize")).value_or(0);
        pl_stats.l2_cache_size_bytes = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "l2cachesize")).value_or(0);
        pl_stats.l3_cache_size_bytes = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "l3cachesize")).value_or(0);
        
        pl_stats.cur_enabled_logical_proc_cores = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "logicalcpu")).value_or(0);
        pl_stats.max_enabled_logical_proc_cores = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "logicalcpu_max")).value_or(0);

        pl_stats.cur_enabled_physical_proc_cores = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "physicalcpu")).value_or(0);
        pl_stats.max_enabled_phyiscal_proc_cores = get_sysctl_value<uint64_t>(get_perf_level_specific_sysctl_name(pl, "physicalcpu_max")).value_or(0);

        this->topology[pl] = pl_stats;
    }
}

auto humanize_size(uint64_t bytes) {
    std::array<std::string, 9> suffixes = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    auto suffix_index = 0;
    auto num = static_cast<double>(bytes);
    while (num >= 1024 && suffix_index < suffixes.size() - 1) {
        num /= 1024;
        suffix_index++;
    }
    return std::format("{:.2f} {}", num, suffixes[suffix_index]);
}

void apple_hardware_stats::print() {
    std::cout << "Current Enabled Logical Proc Cores: " << this->cur_enabled_logical_proc_cores << std::endl;
    std::cout << "Current Enabled Physical Proc Cores: " << this->cur_enabled_physical_proc_cores << std::endl;
    std::cout << "Max Enabled Logical Proc Cores: " << this->max_enabled_logical_proc_cores << std::endl;
    std::cout << "Max Enabled Physical Proc Cores: " << this->max_enabled_phyiscal_proc_cores << std::endl;
    std::cout << "Number of performance levels: " << this->num_perf_levels << std::endl;

    std::cout << "Cache Line Size: " << humanize_size(this->cache_line_size_bytes) << std::endl;
    std::cout << "DRAM Size: " << humanize_size(this->dram_size_bytes) << std::endl;
    std::cout << "Virtual Memory Page Size: " << humanize_size(this->virtual_memory_page_size_bytes) << std::endl;

    std::cout << "----------" << std::endl;
    if (!this->topology.empty()) {
        std::cout << "Topology:" << std::endl;
        for (const auto& pair : this->topology) {
            const auto& level = pair.second;
            std::cout << "Performance Level: " << static_cast<int>(level.perf_level) << std::endl;
            std::cout << "CPUs per L2 Cache: " << level.cpus_per_l2_cache << std::endl;
            std::cout << "CPUs per L3 Cache: " << level.cpus_per_l3_cache << std::endl;
            std::cout << "L1 Instruction Cache Size: " << humanize_size(level.l1_instruction_cache_size_bytes) << std::endl;
            std::cout << "L1 Data Cache Size: " << humanize_size(level.l1_data_cache_size_bytes) << std::endl;
            std::cout << "L2 Cache Size: " << humanize_size(level.l2_cache_size_bytes) << std::endl;
            std::cout << "L3 Cache Size: " << humanize_size(level.l3_cache_size_bytes) << std::endl;
            std::cout << "Current Enabled Logical Proc Cores: " << level.cur_enabled_logical_proc_cores << std::endl;
            std::cout << "Current Enabled Physical Proc Cores: " << level.cur_enabled_physical_proc_cores << std::endl;
            std::cout << "Max Enabled Logical Proc Cores: " << level.max_enabled_logical_proc_cores << std::endl;
            std::cout << "Max Enabled Physical Proc Cores: " << level.max_enabled_phyiscal_proc_cores << std::endl;
            std::cout << "----------" << std::endl;
        }
    }
}

int main() {
    apple_hardware_stats st;
    st.print();
    return 0;
}