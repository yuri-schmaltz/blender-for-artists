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

### PATCH 2: Button Style Consolidation (Planejado)
**Status:** 🔜 Em Planejamento

Objetivo: Criar macros/helpers para consolidar variações de botões.

```c
/* Exemplo de consolidação */
void ui_draw_button_style(
  const uiBut *but,
  const DesignTokensButtonVariant variant,
  const bool is_hovered
);
```

---

### PATCH 3: Token Integration in interface_widgets.cc (Planejado)
**Status:** 🔜 Em Planejamento

Objetivo: Substituir valores hardcoded por tokens em:
- `ui_draw_but()` → usar `tokens->button.min_height`, `tokens->borders.radius_default`
- `ui_draw_button_text()` → usar `tokens->typography.font_size_md`
- Focus ring → usar `tokens->colors.focus_ring` e `tokens->borders.border_width_focus`

---

## 📊 Checklist de Conclusão

- [x] Criar arquivos de tokens (header + impl)
- [x] Definir structs semânticas
- [x] Implementar inicialização com defaults
- [ ] Documentar uso e estender com temas
- [ ] Integrar em ui_draw_but() e variações
- [ ] Testes de renderização (visual regression)
- [ ] Commits e push

---

## 🔮 Próximas Ondas

- **ONDA 3:** UX Polish (collections, empty states, loading)
- **ONDA 4:** Design System Docs & Governance

---

## 📚 Referências

- Tokens internos: `source/blender/editors/interface/interface_design_tokens.h`
- Widget rendering: `source/blender/editors/interface/interface_widgets.cc`
- Tema padrão: `release/datafiles/userdef/userdef_default_theme.c`
