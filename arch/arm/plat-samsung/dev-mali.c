#include <mach/irqs.h>
#include <mach/mali.h>
#include <mach/mali_utgard.h>
#include <linux/platform_device.h>

#define DMA_BIT_MASK(n) (((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))
static u64 samsung_device_dma_mask = DMA_BIT_MASK(32);

static struct mali_gpu_device_data mali_gpu_data = {
        .shared_mem_size = 256*1024*1024,
#ifdef CONFIG_MALI_DVFS
        .utilization_interval = 1000,
        .utilization_handler = mali_gpu_utilization_handler,
#endif
};
static struct resource mali_gpu_resource[] = {
		MALI_GPU_RESOURCES_MALI400_MP4(MALI_BASE_ADDR,
			IRQ_GP_3D,
			IRQ_GPMMU_3D,
			IRQ_PP0_3D,
			IRQ_PPMMU0_3D,
			IRQ_PP1_3D,
			IRQ_PPMMU1_3D,
			IRQ_PP2_3D,
			IRQ_PPMMU2_3D,
			IRQ_PP3_3D,
			IRQ_PPMMU3_3D)
};
  
struct platform_device mali_gpu_device = {
        .name           = MALI_GPU_NAME_UTGARD,
        .id             = 0,
        .num_resources  = ARRAY_SIZE(mali_gpu_resource),
        .resource       = mali_gpu_resource,
        .dev            = {
            .dma_mask = &samsung_device_dma_mask,
            .coherent_dma_mask = DMA_BIT_MASK(32),
            .platform_data = &mali_gpu_data,
        }
};
