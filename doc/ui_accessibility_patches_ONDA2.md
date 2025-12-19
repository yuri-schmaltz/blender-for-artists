# ONDA 2 - Design System Foundation

## 📋 Objetivo
Estabelecer uma camada de design tokens centralizados para:
- Padronizar cores, espaçamento, tipografia em todo o UI
- Facilitar manutenção e evolução do design
- Consolidar padrões de botões e widgets
- Preparar ground para ONDA 3 & 4

## 🎯 PATCHES

### PATCH 1: Design Tokens Header & Implementation
**Status:** ✅ Implementado  
**Arquivos:**
- `source/blender/editors/interface/interface_design_tokens.h` (estruturas de tokens)
- `source/blender/editors/interface/interface_design_tokens.c` (inicialização)

**O que faz:**
- Define structs para:
  - `DesignTokensColors` (paleta semântica: primary, interactive, feedback, focus, node)
  - `DesignTokensSpacing` (xs, sm, md, lg, xl, xxl)
  - `DesignTokensBorders` (widths, radii)
  - `DesignTokensTypography` (font sizes, line heights)
  - `DesignTokensButton` (padding, height, radius)
- Inicializa valores padrão (light theme baseline)
- Fornece API global `g_design_tokens` e `interface_design_tokens_get()`

**Benefícios:**
- ✅ Fonte única de verdade para valores de design
- ✅ Fácil auditoria e ajustes em massa
- ✅ Pronto para expandir com mapeamento de temas

---

### PATCH 2: Button Style Consolidation
**Status:** ✅ Implementado  
**Arquivos:**
- `source/blender/editors/interface/interface_button_styles.h` (structs + API)
- `source/blender/editors/interface/interface_button_styles.c` (implementação)

**O que faz:**
- Define `UIButtonAppearance` struct com cores/estados para bg, border, text
- Implementa 5 variantes de botões:
  - `PRIMARY` — ação principal (azul preenchido)
  - `SECONDARY` — ação secundária (contorno)
  - `TERTIARY` — ação opcional (texto only)
  - `DANGER` — ação destrutiva (vermelho)
  - `GHOST` — ícone-only (mínimo)
- Cada variante tem cores distintas para: normal, hover, pressed, disabled
- API `ui_button_appearance_get()` dispatch para cada variante
- Funções individuais `ui_button_appearance_primary()`, `_secondary()`, etc.

**Benefícios:**
- ✅ Estilos de botão consolidados em um único lugar
- ✅ Sem hardcodes duplicados em interface_widgets.cc
- ✅ Fácil adicionar/ajustar variantes
- ✅ Pronto para integração com GPU drawing primitives

---

### PATCH 3: Token Integration in interface_widgets.cc
**Status:** ✅ Implementado  
**Arquivos:**
- `source/blender/editors/interface/interface_widgets.cc` (integração)

**O que faz:**
- Adiciona include de `interface_design_tokens.h`
- Atualiza `widget_radius_from_zoom()` para usar `tokens->borders.radius_default` com fallback
- Atualiza focus ring para usar:
  - `tokens->colors.focus_ring` para cor (fallback para outline_sel)
  - `tokens->borders.border_width_focus` para largura (fallback para 2.5f)
- Mantém compatibilidade com temas existentes via fallbacks

**Benefícios:**
- ✅ Radius e focus ring agora usam design tokens
- ✅ Consistência visual entre widgets
- ✅ Fácil ajustar globalmente via tokens
- ✅ Backward compatible com temas existentes

---

## 📊 Checklist de Conclusão

- [x] Criar arquivos de tokens (header + impl)
- [x] Definir structs semânticas
- [x] Implementar inicialização com defaults
- [x] Criar variantes consolidadas de botões (header + impl)
- [x] Implementar 5 variantes com cores/estados
- [x] Integrar tokens em widget_radius_from_zoom()
- [x] Integrar tokens no focus ring rendering
- [x] Manter compatibilidade com temas existentes via fallbacks
- [x] Commits e push
- [ ] Testes de renderização visual (próxima iteração)
- [ ] Expandir integração para mais widgets (futuro)

---

## 🔮 Próximas Ondas

- **ONDA 3:** UX Polish (collections, empty states, loading)
- **ONDA 4:** Design System Docs & Governance

---

## 📚 Referências

- Tokens internos: `source/blender/editors/interface/interface_design_tokens.h`
- Widget rendering: `source/blender/editors/interface/interface_widgets.cc`
- Tema padrão: `release/datafiles/userdef/userdef_default_theme.c`
