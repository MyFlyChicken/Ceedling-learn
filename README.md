# Ceedling 单元测试框架示例

[![Ceedling](https://img.shields.io/badge/powered%20by-Ceedling-blue)](https://www.throwtheswitch.org/ceedling)

本项目是一个使用 [Ceedling](https://www.throwtheswitch.org/ceedling) 对嵌入式C代码进行单元测试的简单示例。

## 简介

Ceedling 是一个为C语言构建和测试的自动化工具。它集成了 Unity (单元测试框架)、CMock (Mocking框架) 和 CException (异常处理框架)。本项目旨在演示如何使用 Ceedling 搭建一个基本的C语言单元测试环境。

## 环境准备

在开始之前，请确保您的系统已经安装了 Ruby 和 GCC 编译工具链。

1.  **安装 Ruby**:
    Ceedling 是一个 Ruby gem 包，所以需要先安装 Ruby。您可以从 [Ruby 官网](https://www.ruby-lang.org/en/downloads/) 下载并安装。

2.  **安装 Ceedling**:
    打开终端，使用 gem 命令安装 Ceedling：
    ```bash
    gem install ceedling
    ```

## 项目结构

```
.
├── mcu_sensor_test
│   ├── project.yml      # Ceedling 配置文件
│   ├── build            # 编译生成的文件
│   ├── src              # 源代码
│   │   ├── add.c
│   │   ├── add.h
│   │   ├── bsp_i2c.h
│   │   ├── sensor.c
│   │   └── sensor.h
│   └── test             # 测试代码
│       ├── test_add.c
│       └── test_sensor.c
└── README.md
```

-   `src/`: 存放项目源代码。
-   `test/`: 存放单元测试代码。测试文件通常以 `test_` 开头。
-   `project.yml`: Ceedling 的核心配置文件，用于定义项目路径、依赖、工具链、插件等。
-   `build/`: Ceedling 自动生成的目录，包含编译的中间文件、mock 文件、测试报告等。

## 使用方法

所有 Ceedling 命令都需要在 `mcu_sensor_test` 目录下执行。

1.  **运行所有测试**:
    ```bash
    cd mcu_sensor_test
    ceedling test:all
    ```
    该命令会编译代码、生成 mock、并运行所有测试用例。

2.  **清理项目**:
    ```bash
    ceedling clean
    ```
    该命令会删除 `build` 目录。

3.  **创建新模块**:
    Ceedling 提供了模块生成器插件，可以快速创建源文件、头文件和测试文件。
    ```bash
    ceedling module:create[module_name]
    ```
    例如，创建一个名为 `utils` 的模块：
    ```bash
    ceedling module:create[utils]
    ```
    Ceedling 会在 `src` 目录下生成 `utils.c` 和 `utils.h`，并在 `test` 目录下生成 `test_utils.c`。

4. **测试单个模块**
   如果您只想测试某一个特定的模块，而不是运行所有测试，可以使用 `test:` 任务并指定测试文件的名称。
   ```bash
   ceedling test:<test_file_name>
   ```
   Ceedling 会自动在 `test` 路径下查找匹配的测试文件。您无需提供完整路径或 `.c` 扩展名。

   例如，只测试 `add` 模块：
   ```bash
   ceedling test:test_add
   ```

   只测试 `sensor` 模块：
   ```bash
   ceedling test:test_sensor
   ```
   这在开发和调试特定功能时非常有用，可以节省大量时间。

## 自定义配置

### 添加自定义测试文件夹

如果您想将测试文件存放在默认的 `test/` 目录之外，您需要修改 `project.yml` 文件。

1.  打开 `mcu_sensor_test/project.yml`。
2.  找到 `:paths:` -> `:test:` 部分。
3.  使用 `+:` 前缀添加您的自定义文件夹路径。

例如，如果您想添加一个名为 `another_test_folder` 的文件夹来存放测试文件，可以这样配置：

```yaml
:paths:
  :test:
    - +:test/**
    - -:test/support
    - +:another_test_folder/**  # 添加此行
```

**注意事项**:

*   路径是相对于 `project.yml` 文件所在的位置。
*   `+:` 表示将该路径下的文件添加到测试集合中。
*   `-:` 表示从集合中排除该路径下的文件（例如 `test/support` 目录）。
*   `**` 是一个通配符，表示递归地包含该目录下的所有文件和子目录。

修改配置后，Ceedling 在执行 `test:all` 时会自动查找并运行新路径下的测试文件。

## 示例说明

本项目包含两个示例模块：

1.  **`add` 模块**:
    -   `src/add.c`, `src/add.h`
    -   一个简单的加法函数。
    -   `test/test_add.c` 是对应的测试文件，演示了基本的 Unity断言用法。

2.  **`sensor` 模块**:
    -   `src/sensor.c`, `src/sensor.h`
    -   一个模拟从传感器读取数据的模块，它依赖于 `bsp_i2c.h` 中定义的I2C接口。
    -   `test/test_sensor.c` 是对应的测试文件。它演示了如何使用 CMock 来 mock `bsp_i2c.h` 中的函数，从而在没有硬件的情况下测试 `sensor` 模块的逻辑。


